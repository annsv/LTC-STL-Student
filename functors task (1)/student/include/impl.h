#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
     size_t currentIndex {static_cast<size_t>(BeerBrand::HoeGaarden)};
     BeerBrand operator()()
     {
         if (currentIndex == static_cast<size_t>(BeerBrand::Max))
         {
             currentIndex = static_cast<size_t>(BeerBrand::HoeGaarden);
         }

         return static_cast<BeerBrand>(currentIndex++);
     }
};


/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand brand)
{
    return brand == BeerBrand::Corona || brand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand brand1, BeerBrand brand2)
{
    return getBeerCountry(brand1) == getBeerCountry(brand2);
};

struct MixingPolicy
{
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix(AlcoholDrink alcoholDrink, NonAlcoholDrink nonAlcoholDrink)
    {

        switch(alcoholDrink)
        {
            case AlcoholDrink::Gin:
            {
              if (NonAlcoholDrink::LimeJuice == nonAlcoholDrink)
              {
                  return Cocktail::Gimlet;
              }
              else if (NonAlcoholDrink::GrapefruitJuice == nonAlcoholDrink)
              {
                  return Cocktail::Greyhount;
              }

            break;
            }
            case AlcoholDrink::Whiskey:
            {
                if (NonAlcoholDrink::SevenUp == nonAlcoholDrink)
                {
                    return Cocktail::SevenPlusSeven;
                }

            break;
            }

        }
        return Cocktail::Oops;

    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
