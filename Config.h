#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <string_view>

enum class GasType
{
    ninetyFive,
    ninetyTwo
};

namespace cfg
{
    inline constexpr int gas95Price{ 100 };
    inline constexpr int gas92Price{ 50 };
}

namespace text
{
    const std::wstring waitForPayment{ L"   Ожидание\n    оплаты" };
    const std::wstring sum{ L"  Сумма:" };
    const std::wstring toPay{ L"\n К оплате:" };
    const std::wstring takeChange{ L"   Заберите\n    сдачу" };
    const std::wstring notEnoughMoney{ L" Недостаточно\n   средств\n" };
    const std::wstring chooseGas{ L"\n   Выберите\n    бензин" };
    const std::wstring progress{ L"     Идёт\n заправка...\n Заправлено:\n     " };
}

namespace sizes
{
    // gas station
    inline constexpr int gasStationScaleX{ 7 };
    inline constexpr int gasStationScaleY{ 7 };

    // main screen text
    inline constexpr int mainScreenTextSize{ 20 };

    // buttons
    inline constexpr int insertButtonW{ 84 };
    inline constexpr int insertButtonH{ 14 };
    inline constexpr int insertListBoxH{ 20 };
    inline constexpr int insertListBoxW{ 80 };
    inline constexpr int insertCheckmarkW{ 14 };
    inline constexpr int insertCheckmarkH{ 14 };

    inline constexpr int returnButtonW{ 42 };
    inline constexpr int returnButtonH{ 42 };

    inline constexpr int petrolButtonW{ 25 };
    inline constexpr int petrolButtonH{ 25 };
    inline constexpr int petrolSliderW{ 128 };
    inline constexpr int petrolSliderH{ 15 };

    inline constexpr int utilButtonW{ 20 };
    inline constexpr int utilButtonH{ 20 };

    inline constexpr int changeButtonW{ 84 };
    inline constexpr int changeButtonH{ 21 };
    inline constexpr int changeListBoxH{ 20 };
    inline constexpr int changeListBoxW{ 170 };
}

namespace coords
{
    // gas station
    inline constexpr int gasStationX{ 100 };
    inline constexpr int gasStationY{ -60 };

    // main screen text
    inline constexpr int mainScreenTextX{ 188 };
    inline constexpr int mainScreenTextY{ 210 };

    // buttons
    inline constexpr int insertButtonX{ 282 };
    inline constexpr int insertButtonY{ 360 };
    inline constexpr int insertListBoxX{ insertButtonX + sizes::insertButtonW + 5 };
    inline constexpr int insertListBoxY{ insertButtonY };
    inline constexpr int insertCheckmarkX{ 315 };
    inline constexpr int insertCheckmarkY{ 388 };

    inline constexpr int returnButtonX{ 303 };
    inline constexpr int returnButtonY{ 409 };

    inline constexpr int petrol95ButtonX{ 207 };
    inline constexpr int petrol95ButtonY{ 379 };

    inline constexpr int petrol92ButtonX{ 207 };
    inline constexpr int petrol92ButtonY{ 408 };

    inline constexpr int petrolSliderX{ 200 };
    inline constexpr int petrolSliderY{ 275 };

    inline constexpr int checkMarkButtonX{ 308 };
    inline constexpr int checkMarkButtonY{ 295 };
    inline constexpr int crossButtonX{ 200 };
    inline constexpr int crossButtonY{ 295 };

    inline constexpr int changeButtonX{ 219 };
    inline constexpr int changeButtonY{ 493 };
    inline constexpr int changeListBoxX{ changeButtonX + sizes::changeButtonW + 5 };
    inline constexpr int changeListBoxY{ changeButtonY };

    // cars
    inline constexpr int carStartX{ -1100 };
    inline constexpr int carFuelingX{ 90 };
    inline constexpr int carFinishX{ 1180 };
    inline constexpr int carY{ 300 };
}

#endif