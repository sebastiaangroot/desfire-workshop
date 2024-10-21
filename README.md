# desfire-workshop

## Overview

This repository contains all the material for an introductory workshop about Mifare DESFire security analysis. The goal of the workshop is to gain a basic understanding of the card's function and logical structure, as well as giving participants hands-on experience in analyzing traffic between card and reader, as well as spotting simple implementation defects.

- The `reader` directory contains the code and setup instructions for the card reader used in the challenges.
- The `cards` directory contains configuration instructions for a master card and the card required for challenge 2.
- The `handouts` directory contains all materials to be handed out to workshop participants, including the challenge instructions.

## Materials

- n+k+1 blank Mifare DESFire cards (EV1 or newer)
  - n for number of (pairs of) participants
  - k challenge 2 cards to pass around
  - 1 additional card to act as a master card to test if your reader works
- n Proxmark3 devices
  - n for number of (pairs of) participants
  - Proxmark3 Easy 512K will do for this
- PCSC SmartCard reader
  - HID OMNIKEY 5427 CK and HID OMNIKEY 5022 tested
- (optional) Simple challenge progress indicators & button for reader
  - 3 LEDs
  - 3 330 Ohm resistors
  - 1 button
  - Rasperry Pi (or other platform with some GPIO pins)
