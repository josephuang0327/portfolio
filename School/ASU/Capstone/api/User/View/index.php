<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

#vars
$User_ID = $GLOBALS['myID'];
$stmt = $mysqli->prepare("SELECT * From User WHERE `User_ID` = ?");

$stmt->bind_param("i", $User_ID);
$succeed = $stmt->execute();
$result = $stmt->get_result();

$resultArray = $result->fetch_all(MYSQLI_ASSOC);
die(AppendNoErr($resultArray));
?>
