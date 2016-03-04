<?php
/**
 *配合swoole做的uuid服务
 */
$server_config = [
    'worker_num' => 4,
    'max_request'  => 10000
];
$server_host = '0.0.0.0';
$server_port = 6957;
$sw_server = new swoole_http_server($server_host,$server_port);
$sw_server->set($server_config);

$sw_server->on('request',function($request,$response){
    $data['uuid'] = ku_get_uuid();
    $response->end(json_encode($data));
});