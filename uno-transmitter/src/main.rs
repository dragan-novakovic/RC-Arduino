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
    //let mut led = pins.d13.into_output();
    let up = pins.d10.into_floating_input();
    let down = pins.d9.into_pull_up_input();
    ufmt::uwriteln!(&mut serial, "Got {}!\r", "Start").void_unwrap();
    loop {
        if up.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Napred").void_unwrap();
        }
        if down.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Nazad").void_unwrap();
        }
    }
}
