#![no_std]
#![no_main]

use arduino_hal::prelude::*;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    //Controls
    //Currently using pull down, until I understand pull up xD
    let up = pins.d2.into_floating_input();
    let down = pins.d4.into_floating_input();

    loop {
        if up.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Napred").void_unwrap();
        }
        if down.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Nazad").void_unwrap();
        }
    }
}
