#![no_std]
#![no_main]

use arduino_hal::{hal::Spi, pac::SPI, prelude::*, spi::Settings};
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    //Data line
    let (mut spi, _) = Spi::new(
        dp.SPI,
        pins.d13.into_output(),
        pins.d11.into_output(),
        pins.d12.into_pull_up_input(),
        pins.d10.into_output(),
        Settings::default(),
    );

    //Controls
    //Currently using pull down, until I understand pull up...
    // Aparently when using pull up the value is inverted, and I need to use different input
    let up = pins.d2.into_floating_input();

    loop {
        if up.is_high() {
            ufmt::uwriteln!(&mut serial, "Got {}!\r", "Napred").void_unwrap();
        }
        //send
        nb::block!(spi.send(0b00001111)).void_unwrap();
        // Because MISO is connected to MOSI, the read data should be the same
        let data = nb::block!(spi.read()).void_unwrap();
        ufmt::uwriteln!(&mut serial, "data: {}\r", data).void_unwrap();
        arduino_hal::delay_ms(1000);
    }
}
