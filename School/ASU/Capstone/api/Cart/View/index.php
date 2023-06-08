<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

#vars
$UserID_FK  = $GLOBALS['myID'];

$stmt = $mysqli->prepare("SELECT * From Cart WHERE `UserID_FK` = ?");

$stmt->bind_param("s", $UserID_FK);

$succeed = $stmt->execute();
$result = $stmt->get_result();

$resultArray = $result->fetch_all(MYSQLI_ASSOC);
die(AppendNoErr($resultArray));
