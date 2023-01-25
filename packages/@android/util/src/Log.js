const util = require('util')
const { __android_log_write } = require('android-binding')("android-util");

class Log {
  static VERBOSE = 2;
  static DEBUG = 3;
  static INFO = 4;
  static WARN = 5;
  static ERROR = 6;
  static v(tag, msg, ...data) {
    __android_log_write(this.VERBOSE, String(tag), util.format(msg, ...data));
  }
  static d(tag, msg, ...data) {
    __android_log_write(this.DEBUG, String(tag), util.format(msg, ...data));
  }
  static i(tag, msg, ...data) {
    __android_log_write(this.INFO, String(tag), util.format(msg, ...data));
  }
  static w(tag, msg, ...data) {
    __android_log_write(this.WARN, String(tag), util.format(msg, ...data));
  }
  static e(tag, msg, ...data) {
    __android_log_write(this.ERROR, String(tag), util.format(msg, ...data));
  }
}

module.exports = { Log };