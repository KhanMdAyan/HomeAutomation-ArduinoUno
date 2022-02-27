package de.ullisroboterseite.ursai2sidebar;

import com.google.appinventor.components.runtime.Component;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.view.ViewGroup;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.CheckBox;

import androidx.appcompat.widget.SwitchCompat;
import android.content.res.ColorStateList;
import android.widget.CompoundButton;
import androidx.core.graphics.drawable.DrawableCompat;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;

import android.view.ViewTreeObserver;

import android.util.Log;

class SideBarItemView extends LinearLayout {
    static final String LOG_TAG = UrsAI2SideBar.LOG_TAG;
    final ItemDefinition itemDefinition;
    TextView iconView;
    TextView textView;
    CompoundButton checkBox;
    float density;
    int itemHeight;
    CompoundButton.OnCheckedChangeListener secondListener;
    final SideBarItemView th = this;

    public SideBarItemView(Context context, ItemDefinition idef) {
        super(context);
        this.itemDefinition = idef;

        density = context.getResources().getDisplayMetrics().density;
        itemHeight = (int) (((float) 48) * density);
        int paddingToLeftBorder = (int) (((float) itemDefinition.paddingIcon()) * density);
        int paddingText = (int) (((float) itemDefinition.paddingText()) * density);

        setId(itemDefinition.id);
        setOrientation(LinearLayout.HORIZONTAL);
        setGravity(Gravity.CENTER_VERTICAL + Gravity.LEFT); //19
        setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, itemHeight));

        setEnabled(itemDefinition.enabled);

        if (itemDefinition.hasIcons()) {
            iconView = new TextView(context);
            // 16.0 ist die Standardgröße für den Text. Bei 16.0 Textgröße ist die Icongröße 25.
            iconView.setTextSize(itemDefinition.getTextSize() / 16.0f * 25.0f);
            iconView.setTypeface(itemDefinition.getIconFont());
            iconView.setText(itemDefinition.iconName);
            if (itemDefinition.enabled)
                iconView.setTextColor(itemDefinition.iconColor);
            else
                iconView.setTextColor(itemDefinition.getTextColorInactive()); // Grau

            if (itemDefinition.iconName.isEmpty()) {
                iconView.setText("alarm");
                iconView.setTextColor(0); // transparent
            }

            iconView.setPadding(paddingToLeftBorder, 0, 0, 0);
            addView(iconView);
        }


        textView = new TextView(context);
        textView.setTextSize(itemDefinition.getTextSize());
        if (itemDefinition.enabled) {
            textView.setTextColor(itemDefinition.getTextColor());
            textView.setText(itemDefinition.spanString);

        } else {
            textView.setTextColor((itemDefinition.getTextColorInactive())); // Grau
            textView.setText(itemDefinition.plainText);
        }

        textView.setPadding(paddingText, 0, 0, 0);
        textView.setGravity(19);
        textView.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, itemHeight));
        addView(textView);

        if (!itemDefinition.hasCheckbox)
            return;

        textView.setLayoutParams(new LinearLayout.LayoutParams(10, itemHeight)); // damit auf jeden Fall noch Platz für die CheckBox ist

        if (itemDefinition.useSwitches()) {
            SwitchCompat switchView = new SwitchCompat(context);
            checkBox = switchView;
            DrawableCompat.setTintList(switchView.getThumbDrawable(), itemDefinition.getThumbColors());
            DrawableCompat.setTintList(switchView.getTrackDrawable(), itemDefinition.getTrackColors());
        } else
            checkBox = new CheckBox(context);

        checkBox.setLayoutParams(
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        checkBox.setEnabled(itemDefinition.enabled);
        checkBox.setChecked(itemDefinition.isChecked);

        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                itemDefinition.isChecked = isChecked;
                secondListener.onCheckedChanged( buttonView,  isChecked);
            }
        });

        addView(checkBox);

        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @SuppressLint("NewApi")
            @SuppressWarnings("deprecation")
            @Override
            public void onGlobalLayout() {

                // Ensure you call it only once :
                if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.JELLY_BEAN) {
                    getViewTreeObserver().removeOnGlobalLayoutListener(this);
                } else {
                    getViewTreeObserver().removeGlobalOnLayoutListener(this);
                }
                int tvWidth = itemDefinition.getBarSize() - iconView.getWidth() - checkBox.getWidth()
                        - (int) (((float) 5) * density);
               textView.setLayoutParams(new LinearLayout.LayoutParams(tvWidth, itemHeight));
            }
        });
    }



    public void setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener listener) {
        if (itemDefinition.hasCheckbox)
         secondListener = listener;
    }
}