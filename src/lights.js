var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function getLights() {
  //TODO
}

function getSensors() {
  //TODO
}

function getWhois() {
  //TODO
}

function toggleLight(light) {
  //available: kitchen, corridor, softroom, hardroom
  xhrRequest('http://al2.hskrk.pl/api/v2/light/toggle/' + light, 'GET', function(txt) { console.log(txt);});
}

function toggleKitchenLight() {
  toggleLight('kitchen');
}

Pebble.addEventListener('ready', function(e) {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('appmessage', function (e) {
  console.log("AppMessage received!");
  toggleKitchenLight();
});