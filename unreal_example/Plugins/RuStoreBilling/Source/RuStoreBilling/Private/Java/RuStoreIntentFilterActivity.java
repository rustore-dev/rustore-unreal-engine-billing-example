// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreBilling;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import java.util.List;
import ru.rustore.unitysdk.billingclient.RuStoreUnityBillingClient;

public class RuStoreIntentFilterActivity extends Activity {

	private Class<?> gameActivityClass = null;

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

		if (savedInstanceState == null) {
			RuStoreUnityBillingClient.onNewIntent(getIntent());
			startGameActivity(null);
        }
    }

	@Override
	public void onNewIntent(Intent newIntent)
	{
		super.onNewIntent(newIntent);
		setIntent(newIntent);

		RuStoreUnityBillingClient.onNewIntent(newIntent);
		startGameActivity(newIntent);
	}

	private void startGameActivity(Intent intent) {
		if (gameActivityClass == null) {
			gameActivityClass = findMainActivityClass();
		}

		if (gameActivityClass != null) {
			Intent newIntent = new Intent(this, gameActivityClass);
			if (intent != null) newIntent.putExtras(intent.getExtras());
			startActivity(newIntent);
		}
	}

	private Class<?> findMainActivityClass() {
		Intent intent = new Intent(Intent.ACTION_MAIN);
		intent.addCategory(Intent.CATEGORY_LAUNCHER);
		intent.setPackage(getPackageName());

		List<ResolveInfo> resolveInfos = getPackageManager().queryIntentActivities(intent, 0);
		if (resolveInfos.isEmpty()) {
			return null;
		}

		String mainActivityName = resolveInfos.get(0).activityInfo.name;
		try {
			return Class.forName(mainActivityName);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			return null;
		}
	}
}
