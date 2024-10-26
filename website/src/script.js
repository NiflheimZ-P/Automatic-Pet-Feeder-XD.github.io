let mqttClient;

window.addEventListener("load", (event) => {
  connectToBroker();

  const publishBtn = document.querySelector(".publish");
  publishBtn.addEventListener("click", function () {
    publishMessage();
  });
  console.log("done");
});

function connectToBroker() {
  const clientId = "client" + Math.random().toString(36).substring(7);

  // Change this to point to your MQTT broker
  const host = "mqtt://mqtt-dashboard.com:8884/";

  const options = {
    keepalive: 60,
    clientId: clientId,
    protocolId: "MQTT",
    protocolVersion: 4,
    clean: true,
    reconnectPeriod: 1000,
    connectTimeout: 30 * 1000,
  };

  mqttClient = mqtt.connect(host, options);

  mqttClient.on("error", (err) => {
    mqttClient.end();
    console.log("error");
  });

  mqttClient.on("reconnect", () => {
    console.log("Reconnecting...");
  });

  mqttClient.on("connect", () => {
    console.log("Client connected:" + clientId);
  });

  console.log("connected");
}

function publishMessage() {
  console.log("in");
  const idHolder = document.querySelector("#id");

  const id = parseInt(idHolder.value.trim());
  console.log("nigga", id);

  const topic = "Phycom/Peet/" + id;
  console.log(topic);

  mqttClient.publish(topic, id, {
    qos: 0,
    retain: false,
  });

  idHolder.value = "";
}