var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function toggleKitchenLight() {
  xhrRequest('http://al2.hskrk.pl/api/v2/light/toggle/kitchen', 'GET', function(txt) { console.log(txt);});
}

Pebble.addEventListener('ready', function(e) {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('appmessage', function (e) {
  console.log("AppMessage received!");
  toggleKitchenLight();
});