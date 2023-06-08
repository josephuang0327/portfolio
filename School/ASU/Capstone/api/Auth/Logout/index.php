<?PHP
global $RequireLogin;
$RequireLogin = false;

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
require_once '../../../ensured_login.php';

if (!$GLOBALS['LoginValid'])
{   
     header('Location: ../../../');
}

if (isset($_COOKIE["Token"]) && isset($_COOKIE['UserID'])) {
    $myToken = $_COOKIE['Token'];
    $myID = $_COOKIE['UserID'];

    // 3. Delete from sessions where userid = myid

    $stmt = $mysqli->prepare("DELETE FROM `Session` WHERE `User_ID_FK` = ?");
    $stmt->bind_param("s", $myID);
    $stmt->execute();

    unset($_COOKIE['Token']);
    setcookie('Token', null, -1, '/');

    unset($_COOKIE['UserID']);
    setcookie('UserID', null, -1, '/');
}

 header('Location: ../../../');