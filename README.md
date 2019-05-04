# Technology project: Item tracking with GPS
This is the Git repository for a school project in the class of 'technology'.

## Quick repository overview
The `src` directory contains the source code for the web interface.

The `arduino` directory contains the source code for the Arduino programmable
boards. The subdirectories are named in respect to their functionality.

## Running
### Get repository
Start by cloning the repository with:
```
git clone https://github.com/KongBorup/teknologi-item-locator.git
```

### Tokens
In the `src/js` directory, a `constants.js` file is missing. It contains
something like this:
```js
const MAPBOX_TOKEN = 'YOUR MAPBOX TOKEN HERE';
const LOCATIONIQ_TOKEN = 'YOUR LOCATIONIQ TOKEN HERE';
```
The file has been omitted from the repository because it contains private
information. You will need to create the file yourself and paste the code.

Replace `YOUR MAPBOX TOKEN HERE` and `YOUR LOCATIONIQ TOKEN HERE` with tokens
obtained from [Mapbox's website] and [LocationIQ's website].

### Packages
For the web interface to work, you must download the Leaflet package locally
(version 1.4.0), which can be found on [Leaflet.js' download page]. Put the
contents of the downloaded `.zip` folder into `assets/libs/leaflet`.

Next, add the `.woff` files for the Brandon Grotesque font. You can obtain these
from [Cufon Fonts' website] and put the files in the
`assets/fonts/brandon-grotesque` folder with filenames matching the `fonts.css`
file in the same location. This step is not necessary, but the website will look
better with the correct fonts.

Lastly, install the necessary Arduino packages (check if you have the ones that
are listed in the top of the `.ino` files).

### Actually running
Plug your Arduino boards into your computer, open the Arduino IDE, compile the
code, and upload to your board. Make sure that you have an ethernet cable
plugged into your webserver and that the MAC and IP-addresses match.

Edit the `src/js/main.js` file to send a request to the correct IP-address, and 
then open the `index.html` file. You should see the location of your GPS module.

[Mapbox's website]: https://www.mapbox.com
[LocationIQ's website]: https://locationiq.com
[Leaflet.js' download page]: https://leafletjs.com/download.html
[Cufon Fonts' website]: https://www.cufonfonts.com