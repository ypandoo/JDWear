cordova.define("cordova-plugin-jdwear.jdwear", function(require, exports, module) {
var exec = require('cordova/exec');

exports.coolMethod = function(arg0, success, error) {
    exec(success, error, "jdwear", "coolMethod", [arg0]);
};

});
