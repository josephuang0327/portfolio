<?PHP

global $RequireLogin;
$RequireLogin = false;

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
require_once '../../../ensured_login.php';

if ($GLOBALS['LoginValid']) {
    header('Location: ../../../?');
}

require_once '../../../google/vendor/autoload.php';

// Creating client request to google
$client = new Google_Client();
$client->setClientId($clientID);
$client->setClientSecret($clientSecret);
$client->setRedirectUri($redirectUrl);
$client->addScope('profile');
$client->addScope('email');

if (isset($_GET['code'])) {
    $token = $client->fetchAccessTokenWithAuthCode($_GET['code']);
    $client->setAccessToken($token);

    //Getting User Profile
    $gauth = new Google_Service_Oauth2($client);
    $google_info = $gauth->userinfo->get();
    $email = $google_info->email;
    $name = $google_info->name;
    $idstr = strval($google_info->id);

    $stmt = $mysqli->prepare("SELECT * FROM `User` WHERE `User_ID` = ? ");
    $stmt->bind_param("s", $idstr);
    $succed = $stmt->execute();

    if ($succed) {
        if ($stmt->num_rows === 0) {
            $stmt->close();
            $stmt = $mysqli->prepare("INSERT INTO `User` (`User_ID`, `Name`, `Email`) VALUES (?, ?, ?)");
            $stmt->bind_param("sss", $idstr, $name, $email);
            $succeed = $stmt->execute();

            if (!$succed) {
                header('Location: ../../../?');
            }
        }
    }


    $token = bin2hex(random_bytes(20));

    setcookie("Token", $token, time() + 3600, '/');
    setcookie("UserID", $idstr, time() + 3600, '/');

    $stmt = $mysqli->prepare("INSERT INTO `Session` (`Token`, `User_ID_FK`) VALUES (?, ?); ");
    $stmt->bind_param("ss", $token, $idstr);
    $stmt->execute();
}
header('Location: ../../../?');
