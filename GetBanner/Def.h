/*
   Copyright (C) Oleg Ziakun
*/

#ifndef DEF_H
#define DEF_H

#define INITIAL_SERVER "s-connector.ebuddy.com"
#define INITIAL_PORT 110

#define REDIRECT_REQUEST "e_action=check;e_version=J2ME2;e_device=TestDevice;e_build=1.5;e_operator=TestOperator\n"
#define DATA_REQUEST "e_action=get_banner;e_device=nokia_6300;e_version=J2ME2;e_format=png;e_ip=62.69.184.55;e_operator=dev;e_width=216;e_height=160\n"

#define DECODE_WEB_STR "%20= ;%21=!"

#define BANNER_DATA 35

#define BANNER_TOKEN_SEP ":"
#define END_TOKEN '\n'

#define SPINNER_FILE_NAME "spinner.gif"

#define SUCCESS_VAL "success"
#define ERROR_VAL "KO"

#define SERVER_KEY "e_server"
#define PORT_KEY "e_port"
#define RESULT_KEY "e_result"
#define STATUS_KEY "status"
#define TYPE_KEY "type"
#define TEXT_KEY "text"
#define CONTENT_BASE64_KEY "content_base64"

#define ERROR_WARNING "Error"
#define BUSY_WARNING "Currently busy..."
#define NO_BANNER_FOUND_WARNING "No banner found"

#endif // DEF_H
