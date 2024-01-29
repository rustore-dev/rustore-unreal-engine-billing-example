package ru.rustore.unitysdk.billingclient

import android.content.Intent
import android.util.Log
import ru.rustore.sdk.billingclient.RuStoreBillingClient
import ru.rustore.sdk.billingclient.RuStoreBillingClientFactory
import ru.rustore.sdk.billingclient.model.product.Product
import ru.rustore.sdk.billingclient.model.purchase.PaymentResult
import ru.rustore.sdk.billingclient.model.purchase.Purchase
import ru.rustore.sdk.billingclient.presentation.BillingClientTheme
import ru.rustore.sdk.billingclient.provider.logger.ExternalPaymentLogger
import ru.rustore.sdk.billingclient.utils.pub.checkPurchasesAvailability
import ru.rustore.sdk.billingclient.utils.resolveForBilling
import ru.rustore.sdk.core.exception.RuStoreException
import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult
import ru.rustore.sdk.core.tasks.OnCompleteListener
import ru.rustore.unitysdk.billingclient.callbacks.ConfirmPurchaseListener
import ru.rustore.unitysdk.billingclient.callbacks.DeletePurchaseListener
import ru.rustore.unitysdk.billingclient.callbacks.PaymentResultListener
import ru.rustore.unitysdk.billingclient.callbacks.ProductsResponseListener
import ru.rustore.unitysdk.billingclient.callbacks.PurchaseInfoResponseListener
import ru.rustore.unitysdk.billingclient.callbacks.PurchasesResponseListener
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener

object RuStoreUnityBillingClient {

	private var allowErrorHandling: Boolean = false
	private lateinit var billingClient: RuStoreBillingClient
	private var isInitialized: Boolean = false

	fun setErrorHandling(allowErrorHandling: Boolean) {
		this.allowErrorHandling = allowErrorHandling
	}

	fun getErrorHandling() : Boolean {
		return allowErrorHandling
	}

	fun init(consoleApplicationId: String, deeplinkScheme: String, allowErrorHandling: Boolean, enableLogs: Boolean, metricType: String) {
		if (isInitialized) return

		this.allowErrorHandling = allowErrorHandling

		PlayerProvider.getCurrentActivity()?.run {
			billingClient = RuStoreBillingClientFactory.create(
				context = application,
				consoleApplicationId = consoleApplicationId,
				deeplinkScheme = deeplinkScheme,
				themeProvider = RuStoreBillingClientThemeProviderImpl,
				debugLogs = enableLogs,
				externalPaymentLoggerFactory = { tag -> BillingClientLogger(tag) },
				internalConfig = mapOf("type" to metricType)
			)
		}

		isInitialized = true;
	}

	fun checkPurchasesAvailability(listener: FeatureAvailabilityListener) {
		PlayerProvider.getCurrentActivity()?.run {
			RuStoreBillingClient.checkPurchasesAvailability(application)
				.addOnCompleteListener(object : OnCompleteListener<FeatureAvailabilityResult> {
					override fun onFailure(throwable: Throwable) {
						handleError(throwable)
						listener.OnFailure(throwable)
					}

					override fun onSuccess(result: FeatureAvailabilityResult) {
						listener.OnSuccess(result)
					}
				})
		}
	}

	fun getProducts(productIds: Array<String>, listener: ProductsResponseListener) {
		billingClient.products.getProducts(
				productIds = productIds.asList()
		).addOnCompleteListener(object : OnCompleteListener<List<Product>> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: List<Product>) {
				listener.OnSuccess(result)
			}
		})
	}

	fun getPurchases(listener: PurchasesResponseListener) {
		billingClient.purchases.getPurchases()
				.addOnCompleteListener(object : OnCompleteListener<List<Purchase>> {
					override fun onFailure(throwable: Throwable) {
						handleError(throwable)
						listener.OnFailure(throwable)
					}

					override fun onSuccess(result: List<Purchase>) {
						listener.OnSuccess(result)
					}
				})
	}

	fun getPurchaseInfo(purchaseId: String, listener: PurchaseInfoResponseListener) {
		billingClient.purchases.getPurchaseInfo(purchaseId)
			.addOnCompleteListener(object : OnCompleteListener<Purchase> {
				override fun onFailure(throwable: Throwable) {
					handleError(throwable)
					listener.OnFailure(throwable)
				}

				override fun onSuccess(result: Purchase) {
					listener.OnSuccess(result)
				}
			})
	}

	fun purchaseProduct(productId: String, orderId: String?, quantity: Int, developerPayload: String?, listener: PaymentResultListener) {
		billingClient.purchases.purchaseProduct(
				productId = productId,
				orderId = orderId,
				quantity = quantity,
				developerPayload = developerPayload
		).addOnCompleteListener(object : OnCompleteListener<PaymentResult> {
			override fun onFailure(throwable: Throwable) {
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: PaymentResult) {
				listener.OnSuccess(result)
			}
		})
	}

	fun confirmPurchase(purchaseId: String, listener: ConfirmPurchaseListener) {
		billingClient.purchases.confirmPurchase(
				purchaseId = purchaseId
		).addOnCompleteListener(object : OnCompleteListener<Unit> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: Unit) {
				listener.OnSuccess()
			}
		})
	}

	fun deletePurchase(purchaseId: String, listener: DeletePurchaseListener) {
		billingClient.purchases.deletePurchase(
				purchaseId = purchaseId
		).addOnCompleteListener(object : OnCompleteListener<Unit> {
			override fun onFailure(throwable: Throwable) {
				handleError(throwable)
				listener.OnFailure(throwable)
			}

			override fun onSuccess(result: Unit) {
				listener.OnSuccess()
			}
		})
	}

	fun setThemeCode(themeCode: Int) {
		RuStoreBillingClientThemeProviderImpl.setTheme(BillingClientTheme.values()[themeCode])
	}

	fun getThemeCode(): Int = RuStoreBillingClientThemeProviderImpl.getTheme().ordinal

	private fun handleError(throwable: Throwable) {
		PlayerProvider.getCurrentActivity()?.let { activity ->
			if (allowErrorHandling && throwable is RuStoreException) {
				throwable.resolveForBilling(activity)
			}
		}
	}

	@JvmStatic
	fun onNewIntent(intent: Intent) {
		if (!isInitialized) return
		billingClient.onNewIntent(intent)
	}

	class BillingClientLogger(private val tag: String) : ExternalPaymentLogger {

		override fun d(e: Throwable?, message: () -> String) {
			Log.d(tag, message.invoke(), e)
		}

		override fun e(e: Throwable?, message: () -> String) {
			Log.e(tag, message.invoke(), e)
		}

		override fun i(e: Throwable?, message: () -> String) {
			Log.i(tag, message.invoke(), e)
		}

		override fun v(e: Throwable?, message: () -> String) {
			Log.v(tag, message.invoke(), e)
		}

		override fun w(e: Throwable?, message: () -> String) {
			Log.w(tag, message.invoke(), e)
		}
	}
}
