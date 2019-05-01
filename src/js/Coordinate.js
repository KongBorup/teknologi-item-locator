class Coordinate {
  constructor({ lat, long }) {
    // Verify integrity of input
    if (!lat || !long) {
      throw new Error('An object with `lat` and `long` fields must be provided');
    }

    if (
      !(lat.degs && lat.mins && lat.secs && lat.dir) ||
      !(long.degs && long.mins && long.secs && long.dir)
    ) {
      throw new Error('All fields `degs`,`mins`,`secs`,`dir` must be provided in `lat` and `long` entries');
    }

    this.lat = lat;
    this.long = long;
  }

  static fromDecimals(lat, long) {
    const { abs, floor } = Math;

    const latDir = lat < 0 ? 'S' : 'N';
    const longDir = long < 0 ? 'W' : 'E';

    const latDegs = floor(abs(lat));
    const latMins = floor((abs(lat) - latDegs) * 60);
    const latSecs = (abs(lat) - (latDegs + latMins / 60)) * 3600;

    const longDegs = floor(abs(long));
    const longMins = floor((abs(long) - longDegs) * 60);
    const longSecs = (abs(long) - (longDegs + longMins / 60)) * 3600;

    return new Coordinate({
      lat: {
        degs: latDegs,
        mins: latMins,
        secs: latSecs,
        dir: latDir,
      },
      long: {
        degs: longDegs,
        mins: longMins,
        secs: longSecs,
        dir: longDir,
      },
    });
  }

  coordMap(callback) {
    return [this.lat, this.long].map(callback);
  }

  toDisplayStrings() {
    return this.coordMap(({ degs, mins, secs, dir }) => `${degs}° ${mins}' ${secs}" ${dir}`);
  }

  toDecimals() {
    return this.coordMap(({ degs, mins, secs, dir }) => {
      const dec = degs + (mins / 60) + (secs / 60 / 60);
      const dirFactor = (dir === 'W' || dir === 'S') ? -1 : 1;
      
      return dec * dirFactor;
    });
  }
}