# My Tech Wearables
 1) Cloth cat ears wearable with led strips!
    
    I wanted to make life like cat ears for a long time, combined with an obsession for glowing stuff.
    
    The lights are powered by a 12V battery, 32 WS2815 led's and a 'lilypad' based on the Attiny85

    # The process:

    Figuring out the shape:

        There are plenty of available cat ears around they're usually just squished cloth that looks cutesy when worn but they don't look realistic at all.
        
        First i sculptured miniature ear pieces out of polymerclay and unwrapped their shape onto paper creating a mold for the cloth design, the intuition behind it came as i was helping a friend to make a helmet. we unwrapped the shape of the helmet onto the foam we were shaping. creating highly refined scraps to that are stitchable ontop of the helmet without bends or oddities.
    Wiring and Coding:

        Wiring everything together is simple enough.
        Coding it did pose an issue despite mostly being taken care of by the FastLED library. The attiny85 only has 6k of memory, this reduced the number of petterns possible and the features available as most of the memory is being clogged by the library. 
        To achieve the end result i desired some corners were cut, such as no input support for a blushing effect.
        ontop of that I have minimized the program's size as much as i could figure out by reducing varibles, rounding constants to their closests minimal binary representation and cutting conditional statements. 

    Take aways:

        WS2815 were the wrong choice, WS2813, designed for 5V they're more suitable for the project and can allow usage of battery packs you already own
        Attiny85 is very limited in its storage. sadly it is as cheap and as tiny as it comes, in the future it is worth considering investing more into this area.
         





