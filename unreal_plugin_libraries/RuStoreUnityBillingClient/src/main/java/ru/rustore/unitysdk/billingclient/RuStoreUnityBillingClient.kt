package ru.rustore.unitysdk.billingclient

import android.content.Intent
import android.util.Log
import ru.rustore.sdk.billingclient.RuStoreBillingClient
import ru.rustore.sdk.billingclient.RuStoreBillingClientFactory
import ru.rustore.sdk.billingclient.presentation.BillingClientTheme
import ru.rustore.sdk.billingclient.provider.logger.ExternalPaymentLogger
import ru.rustore.sdk.billingclient.utils.pub.checkPurchasesAvailability
import ru.rustore.sdk.billingclient.utils.resolveForBilling
import ru.rustore.sdk.core.exception.RuStoreException
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
				.addOnSuccessListener { result ->
					listener.OnSuccess(result)
				}
				.addOnFailureListener { throwable ->
					handleError(throwable)
					listener.OnFailure(throwable)
				}
		}
	}

	fun getProducts(productIds: Array<String>, listener: ProductsResponseListener) {
		billingClient.products.getProducts(productIds.asList())
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun getPurchases(listener: PurchasesResponseListener) {
		billingClient.purchases.getPurchases()
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun getPurchaseInfo(purchaseId: String, listener: PurchaseInfoResponseListener) {
		billingClient.purchases.getPurchaseInfo(purchaseId)
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun purchaseProduct(productId: String, orderId: String?, quantity: Int, developerPayload: String?, listener: PaymentResultListener) {
		billingClient.purchases.purchaseProduct(
				productId = productId,
				orderId = orderId,
				quantity = quantity,
				developerPayload = developerPayload
		)
			.addOnSuccessListener { result ->
				listener.OnSuccess(result)
			}
			.addOnFailureListener { throwable ->
				listener.OnFailure(throwable)
			}
	}

	fun confirmPurchase(purchaseId: String, listener: ConfirmPurchaseListener) {
		billingClient.purchases.confirmPurchase(purchaseId)
			.addOnSuccessListener {
				listener.OnSuccess()
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
	}

	fun deletePurchase(purchaseId: String, listener: DeletePurchaseListener) {
		billingClient.purchases.deletePurchase(purchaseId)
			.addOnSuccessListener {
				listener.OnSuccess()
			}
			.addOnFailureListener { throwable ->
				handleError(throwable)
				listener.OnFailure(throwable)
			}
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
