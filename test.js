const { System, SystemProperties, Build } = require(".")

// console.log(System.uname())

// Should throw error
// System.cmd("cmd battery reset -f")

const locked = SystemProperties.get("ro.boot.flash.locked")

// console.log(Build.LOCKED)


console.log(Build.VERSION.require(33))