const {System} =require(".")

// console.log(System.uname())

// Should throw error
System.cmd("cmd battery reset -f")