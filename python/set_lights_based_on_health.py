import asyncio, time, math, sys
from kasa import SmartLightStrip


async def set_smart_lights_color(light_strip: SmartLightStrip, hsv_value: int):
    await light_strip.update()  # Request the update
    await light_strip.set_hsv(hsv_value, 100, 100, transition=1000)


def calculate_next_hsv_value(heatlh_value: float):
    if heatlh_value >= 100:
        return 100
    elif heatlh_value <= 0:
        return 0
    else:
        return math.floor(heatlh_value)  

def main(heatlh_value: float):
    light_strip = SmartLightStrip("192.168.1.68")
    hsv_value = calculate_next_hsv_value(heatlh_value)

    asyncio.run(set_smart_lights_color(light_strip, hsv_value))


if __name__ == "__main__":
    if len(sys.argv) == 2:
        if sys.argv[1].isdecimal() == False:
            print(f"Error: Argument '{sys.argv[1]}' is not a valid decimal value.")
            exit(1)
        main(float(sys.argv[1]))
        exit(0)
    else:
        print(
            "Error: Not enough args passed\nUsage: python health_tracker <heatlh_value>"
        )
        exit(1)
