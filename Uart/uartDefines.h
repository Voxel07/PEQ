#define uart_version "at+version"
// at+set_config=lora:join_mode:0 //OTAA
// at+set_config=lora:join_mode:1 //ABP
// at+set_config=lora:class:0 //Class A
// at+set_config=lora:class:1 //Class B
// at+set_config=lora:class:2 //Class C
// at+set_config=lora:region:EU868 //Region
// at+set_config=lora:dev_eui:8a26fea9c6009b23
// at+set_config=lora:app_eui:8a26fea9c6009b23
// at+set_config=lora:app_key:ece7792e30c6639ffb5101564804ac30
#define lora_send "at+send=lora:2:" //Send message
