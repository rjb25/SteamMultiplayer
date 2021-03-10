// Fill out your copyright notice in the Description page of Project Settings.

#include "TempRacingWidget.h"
#include "Components/TextBlock.h"
	void UTempRacingWidget::setTime(float time) {
		if (Time) {
			Time->SetText(FText::AsNumber(time));
		}
	}
	void UTempRacingWidget::setLap(int lap) {
		if (Lap) {
			Lap->SetText(FText::AsNumber(lap));
		}

	}
	void UTempRacingWidget::setPlace(int place) {
		if (Place) {
			Place->SetText(FText::AsNumber(place));
		}
	}
