/*
 This is free and unencumbered software released into the public domain - see UNLICENSE for details.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUDP.h>

// Options
#define use_button // Wake up at the push of a button
#define use_leds // Use LEDs for a simple status readout
#define use_dhcp // Use DHCP to automatically obtain an IP address

// Globals
const int delay_time = 500;
const byte first_six_bytes[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
EthernetUDP udp_client;

// LED pin configuration
#ifdef use_leds
  const int led_red = 8; // Used when there's no connection the the LAN or when there's an error
  const int led_yellow = 7; // Used to show that the device is connected to the LAN and ready
  const int led_green = 6; // Used when the device is sending WOL packets
#endif

// Button pin configuration
#ifdef use_button
  const int button = 5;
#endif

// Ethernet configuration
byte arduino_mac[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66}; // Arduino's MAC address
const byte broadcast_ip[] = {255, 255, 255, 255}; // Broadcast IP address

#ifndef use_dhcp
  const byte static_ip[] = {172, 16, 0, 10}; // Arduino IP address
#endif

// Target configuration
const byte target_mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}; // PC's MAC address

void setup() {
  // Initialise LEDs
  #ifdef use_leds
    pinMode(led_red, OUTPUT);
    pinMode(led_yellow, OUTPUT);
    pinMode(led_green, OUTPUT);

    digitalWrite(led_red, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW);
  #endif

  // Initialise button
  #ifdef use_button
    pinMode(button, INPUT);
    digitalWrite(button, HIGH);
  #endif

  // Get an IP
  #ifdef use_dhcp
    // Gets an IP via DHCP, and retries until it gets one
    boolean got_ip = false;
    while (!got_ip) {
      // No assigned IP
      #ifdef use_leds
        digitalWrite(led_red, HIGH);
      #endif

      // Get an IP via DHCP
      if (Ethernet.begin(arduino_mac) != 0) {
        got_ip = true;

        // Device is ready to send WOL packets
        #ifdef use_leds
          digitalWrite(led_red, LOW);
          digitalWrite(led_yellow, HIGH);
        #endif

      } else {
        // Wait before retrying
        delay(delay_time);
      }
    }
  #else
    // Static IP setup
    Ethernet.begin(arduino_mac, static_ip);
  #endif
}

void send_wol_packet() {
  udp_client.begin(7);
  udp_client.beginPacket(broadcast_ip, 7);

  udp_client.write(first_six_bytes, sizeof first_six_bytes);

  for (int i = 0; i < 16; i++) {
    udp_client.write(target_mac, sizeof target_mac);
  }

  udp_client.endPacket();
  udp_client.stop();
}

void loop() {
  #ifdef use_button
    // Wait until the button is pressed
    while (digitalRead(button) == LOW) {
      #ifdef use_leds
        digitalWrite(led_yellow, LOW);
        digitalWrite(led_green, HIGH);
      #endif

      delay(delay_time);

      send_wol_packet();

      delay(delay_time);

      #ifdef use_leds
        digitalWrite(led_green, LOW);
        digitalWrite(led_yellow, HIGH);
      #endif
    }

  #else
    // Send 10 WOL packets then stop
    boolean sent_wol_packet = false;
    if (!sent_wol_packet) {
      for (int i = 0; i < 10; ++i) {
        send_wol_packet();
      }

      #ifdef use_leds
        digitalWrite(led_yellow, LOW);
        digitalWrite(led_green, HIGH);
      #endif

      sent_wol_packet = true;
    }
  #endif
}
