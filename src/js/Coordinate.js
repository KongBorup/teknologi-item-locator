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