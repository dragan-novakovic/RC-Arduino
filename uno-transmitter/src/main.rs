#![no_std]
#![no_main]

use arduino_hal::{hal::Spi, pac::SPI, prelude::*};
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    //Data line
    // let spi = Spi::new(SPI, sclk, mosi, miso, cs, settings);

    //Controls
    //Currently using pull down, until I understand pull up...
    // Aparently when using pull up the value is inverted, and I need to use different input
    let up = pins.d2.into_floating_input();

    loop {
        if up.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Napred").void_unwrap();
            // Spi::send(spi, b"a");
        }
    }
}
