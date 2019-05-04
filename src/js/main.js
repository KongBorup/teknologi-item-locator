async function getCoordinates() {
  const url = 'http://192.168.137.128';
  const res = await fetch(url);
  const [lat, long] = eval(await res.text());
  const [latDeg, latMin, latSec, latDir] = lat;
  const [longDeg, longMin, longSec, longDir] = long;

  return new Coordinate({
    lat: {
      degs: latDeg,
      mins: latMin,
      secs: latSec,
      dir: latDir,
    },
    long: {
      degs: longDeg,
      mins: longMin,
      secs: longSec,
      dir: longDir,
    },
  });
}

(async () => {
  const coord = await getCoordinates();
 
  const [latStr, longStr] = coord.toDisplayStrings();
  document.getElementById('lat').textContent = latStr;
  document.getElementById('long').textContent = longStr;
  
  const map = new LeafletMap('map', coord);
  const marker = map.addMarker(coord);

  const [lat, long] = coord.toDecimals();
  const url = `https://eu1.locationiq.com/v1/reverse.php?key=${LOCATIONIQ_TOKEN}&lat=${lat}&lon=${long}&format=json`;
  const res = await fetch(url);
  const location = await res.json();

  console.log(location);

  document.getElementById('address').textContent = location.display_name;
})();