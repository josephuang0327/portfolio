<?php
global $RequireLogin;
$RequireLogin = false;

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
require_once '../../../ensured_login.php';
require_once '../../../google/vendor/autoload.php';

// Creating client request to google
$client = new Google_Client();
$client->setClientId($clientID);
$client->setClientSecret($clientSecret);
$client->setRedirectUri($redirectUrl);
$client->addScope('profile');
$client->addScope('email');

$ReturnArr['SSO'] = "Google";
$ReturnArr['URL'] = $client->createAuthUrl();
$ReturnArr['LoginStatus'] = $isUserLoggedin;

die(json_encode($ReturnArr));