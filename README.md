# Arduino-MKR1000-PlantMonitor
Plant Communicator Code for the MKR1000

## Intro
In this lab we will build a plant soil hydration monitor and have it report soil mosture back to us.  The moisture levels will be logged for trend analysis and alerts will be sent to us to warn us when the plant needs more water.

This lab is from the Arduino MKR1000 site:
https://create.arduino.cc/projecthub/arduino/plant-communicator-7ea06f



## Pre-Requisites:

### Power Warning:
The microcontroller on the MKR1000 runs at 3.3V, which means that you must never apply more than 3.3V to its Digital and Analog pins. Care must be taken when connecting sensors and actuators to assure that this limit of 3.3V is never exceeded. **Connecting higher voltage signals, like the 5V commonly used with the other Arduino boards, will damage the MKR1000**.

### How to use a breadboard
You will use a breadboard later in this lab, familiarizing yourself with how they work will help to make that part of the lab easier. https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard

### Setup your workstation (computer) for Arduino development

In this section we have to setup our computer to do Arduino development.  This setup will intall the programs we need to write code for the arduino and send it to the arduino to run.

The steps for this start here:
 https://www.arduino.cc/en/Guide/MKR1000#toc2

  1. Install the Arduino Integrated Development Environment (IDE): https://www.arduino.cc/en/Main/Software
  2. add the Atmel SAMD Core - https://www.arduino.cc/en/Guide/Cores the instructions are good and have images, but the major steps and some things to watch for are called out below.
    * Tools>Boards>Board Manager
    * Scroll down and find **Arduino SAM Boards** -

      ***NOTE!*** It is important to pay attention here, there may be more than one package with this name.  You want the **This package includes** to lists **Arduino/Genuino MKR1000**.

    * Choose the most recent version from the version drop down in the **Arduino SAM Boards** section and click **Install** (at the time I did this the tutorial page says 1.6.6, and my version was 1.6.18)
  3. Install may take a few minutes, just wait.  It will say **Installed** in the boards section when it is installed, and be listed in the board manager for you to select.
  4. Select the MKR1000 in the Board Manager.
  5. Follow the Driver Installation instructions for your Operating System (Win/Mac/Linux).

  ## Let's Test it out!

  Okay, now that we have all that stuff installed, let's see if we can run a sample program.

  Plug the Arduino board into your computer using the supplied black micro USB cable.
  Then follow the steps from "Open your first sketch", stop when you reach "learn more on the Desktop IDE": https://www.arduino.cc/en/Guide/MKR1000#toc4

  If the light blinks, then you have run your first program on the Arduino board!

# Let's Make a Plant Soil Sensor!

  We are going to follow this Tutorial: https://create.arduino.cc/projecthub/arduino/plant-communicator-7ea06f
  What I want you to do, is read read the notes here for any hiccups that I might warn about and then follow the instructions on the site for that section.  I am also going to change some of the order of things.

## Start a new sketch
  1. File>New
  2. File>Save (save you work!)

## Setting up the Board

You can read about installing and working with libraries here: https://www.arduino.cc/en/Guide/Libraries

The key steps are outlined below:

  1. Add WiFi to your project.
      * Sketch>Include Library>WiFi
      * File>Save

  2. Add the RTCzero Library
      * This one needs to be installed from the Library Manager first.
      * Sketch>Include Library>Manage Libraries...
      * In the 'Filter Your Search' box at the top, enter **RTCzero**
      * Click the option "RTCzero by Arduino"
      * Confirm that that it says "For .... MKR1000" in the description
      * Select the most recent version and click **Install**

  3.  Click 'Close'

  4. Sketch>Include Library>RTCzero

  5. Your sketch should now have the following code at the top:
  ```
  #include <RTCZero.h>

  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WiFiClient.h>
  #include <WiFiServer.h>
  ```

  These lines will give us access to the code in those external libraries.
  In this way, we do not have to write our own WiFi controllers we can use one that is written and tested and we know works.

  6. File>Save

## Starting our code

The lab at the website starts with setting up external site accounts and HTTP requests.
I think those things are cool, but let's do that later.  No need to get complicated early.

**NOTE** Does this code look a little different than code you may have written before?
That's because it is C.  If you want to learn more about C you can do that here: http://www.learn-c.org/en/
C is a a great programming language to learn with, it makes you do all the work.
This may seem bad, but it also means you learn memory management better.  And many modern languages are "c-based" just like many spoken languages are "latin based".  You can see a family-tree of a majority of programming languages here: https://blogs.ucl.ac.uk/ucl-student-blog/a-brief-history-of-programming-languages-a-review-of-codes-that-changed-the-world/

**NOTE 2** Why choose one programming language over another?  Each language has certain things that it is best at.  Just like Darwins finches they each evolved to do something slightly better.  Many small platforms with limited memory still run on C because you can write small and efficient programs with it - a great benefit when you don't have much computing power to work with, like on a small Arduino board.

### Hello World!

Every computer program starts with a basic "Hello World!".  We use this to show that we have the program running and can print human readable output - that we can tell the computer things and it can tell us things.

**Note** Comments in code are lines that are surrounded in ```/* This is a comment */``` or started with ```// This is a comment ``` we use these types of lines in code to leave ourselves little notes about what the program is doing.  The rule is to leave as many comments as are necessary.  If you have a small program and are an experienced programmer you may not need comments, but if you are new write TONS of comments for yourself. *I am going to write many comments so you know what is going on, so watch closely for them*

# This is needed to update the WiFi Sheild https://www.arduino.cc/en/Tutorial/FirmwareUpdater

Copy Paste this code into your Arduino editor.
```
/* These are header includes we don't need them at the moment,
 * but we added them in the earlier steps so I left them.  
 * These headers are little libraries of code someone else has written and tested that we can use!
 */
#include <RTCZero.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

/*The first method called.
 * This method is called once at the start of the app running.
 * It is used to setup and initialize connections and things
 * needed in the program.
 */
void setup() {
  Serial.begin(9600);
  while (!Serial) {
   delay(2000);
  }

  Serial.println("Plant Communicator 1.0 Running!");
  Serial.println("Begin setup...");
    //We will put setup steps here later.
  Serial.println("Setup complete!");
}

/*The main body of our program
 * It will run over and over until we tell it to stop.
 */
void loop() {
  // put your main code here, to run repeatedly:
}
```
