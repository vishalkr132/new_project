#include <stdio.h>
#include "MQTTClient.h"

#define ADDRESS "tcp://localhost:1883"
#define CLIENTID "tempId"
#define TOPIC = "temp"
#define QOS 1
#define TIMEOUT 10000L


int main()
{

    MQTTClient client;
    MQTTClient_connectOptions conn_opt = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmes = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token
    int rc;


    // create instance of mqtt client

    MQTTClient_create(&client , ADDRESS , CLIENTID , MQTTCLIENT_PERSISTENCE_NONE , NULL);
    conn_opt.keepAliveInterval = 20;
    conn_opt.cleansession = 1;

    if(rc = MQTTClient_connect(client , &conn_opt) != MQTTCLIENT_SUCCESS)
    {
        printf("failed to connect\n");
    }
    int temp = 20;
    char buffer[50];
    sprintf(buffer , "temp = %d" , temp);

    pubmes.payload = buffer;
    pubmes.payloadlen = strlen(buffer);
    pubmes.qos = QOS;
    pubmes.retained = 0;

    MQTTClient_publishMessage(client , TOPIC , &pubmes , &token);


    return 0;
}