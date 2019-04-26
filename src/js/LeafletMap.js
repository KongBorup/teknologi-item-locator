// Utility class for interacting with Leaflet maps
// Requires the Leaflet library to be loaded
class LeafletMap {
  /**
   * @param {String} elementId - ID of target div element
   * @param {Coordinate} startCoords - View at coordinates
   */
  constructor(elementId, startCoords) {
    const map = L
      .map(elementId)
      .setView(startCoords.toDecimals(), 13);

    // L.tileLayer('https://api.mapbox.com/styles/v1/mapbox/dark-v10/tiles/256/{z}/{x}/{y}?access_token={accessToken}', {
    L.tileLayer('https://api.mapbox.com/styles/v1/karlo2001/cjuxyxfpd0bgo1fpso1nch8k4/tiles/256/{z}/{x}/{y}?access_token={accessToken}', {
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, <a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
        maxZoom: 18,
        id: 'mapbox.streets',
        accessToken: MAPBOX_TOKEN,
    }).addTo(map);

    this.map = map;
  }

  /**
   * @param {Coordinate} coord - The marker's coordinate 
   */
  addMarker(coord) {
    return L.marker(coord.toDecimals()).addTo(this.map);
  }

  /**
   * @param {Leaflet Marker} marker - Marker to add popup to.
   * @param {String} content - The popup's HTML content
   */
  static addPopupToMarker(marker, content = '') {
    marker.bindPopup(content).openPopup();
  }
}
