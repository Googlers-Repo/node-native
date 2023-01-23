import { createRequire } from 'module';
import util from 'util'

const require = createRequire(import.meta.url);
const { getprop, setprop } = require("/data/data/io.spck/files/android-log/build/Release/android-os.node");

class SystemProperties {
  static PROP_VALUE_MAX = 91;

  static get(key, def = '') {
    return String(getprop(key)) || def
  }

  static getList(key, separator = ',') {
    return String(getprop(key)).split(separator) || []
  }

  static getNumber(key, def = 0) {
    return Number(getprop(key)) || def
  }

  static getBoolean(key, def = false) {
    return getprop(key) === 'true' || def
  }

  static set(key, val) {
    if (val != null && !key.startsWith("ro.") && val.length > this.PROP_VALUE_MAX) {
      throw new Error("value of system property '" + key +
        "' is longer than " + this.PROP_VALUE_MAX + " bytes: " + val);
    }
    setprop(key, val);
  }
}

export  {SystemProperties};