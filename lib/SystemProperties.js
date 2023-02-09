const { BaseProperties } = require("bindings")("android-os.node");

class SystemProperties extends BaseProperties {
  static TAG = "NodeSystemProperties";
  static PROP_VALUE_MAX = 91;
  static TRACK_KEY_ACCESS = false;

  constructor() {
    super();
  }

  static get(key, def = "") {
    try {
      return super.get(key, def);
    } catch {
      return "";
    }
  }

  static getList(key, sep = ",") {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof sep != "string") {
      throw new TypeError("The separator should be an string");
    }

    const result = this.get(key, "");

    return result != "" ? result.split(sep) : [];
  }

  static getBoolean(key, def = false) {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof def != "boolean") {
      throw new TypeError("The default value should be an boolean");
    }

    return /^true$/i.test(this.get(key, String(def)));
  }

  static getInt(key, def = 0) {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof def != "number") {
      throw new TypeError("The default value should be an number");
    }

    const result = this.get(key, String(def));

    if (/\d/.test(result)) {
      return Number(result);
    } else {
      return def;
    }
  }

  static set(key, val) {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof val != "string") {
      throw new TypeError("The value should be an string");
    }

    if (val != null && !key.startsWith("ro.") && val.length > this.PROP_VALUE_MAX) {
      throw new Error(
        "value of system property '" + key + "' is longer than " + this.PROP_VALUE_MAX + " bytes: " + val
      );
    }
    super.set(key, String(val));
  }

  static setInt(key, val) {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof val != "number") {
      throw new TypeError("The value should be an number");
    }

    this.set(key, String(val));
  }

  static setBoolean(key, val) {
    if (typeof key != "string") {
      throw new TypeError("The key should be an string");
    }

    if (typeof val != "boolean") {
      throw new TypeError("The value should be an boolean");
    }

    this.set(key, String(val));
  }
}

module.exports = { SystemProperties };
