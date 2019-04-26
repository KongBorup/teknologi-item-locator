(async () => {
  const coord = new Coordinate({
    lat: {
      degs: 39,
      mins: 6,
      secs: 59,
      dir: 'N',
    },
    long: {
      degs: 125,
      mins: 48,
      secs: 21,
      dir: 'E',
    },
  });
  
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