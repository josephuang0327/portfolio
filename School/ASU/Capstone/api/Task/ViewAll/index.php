<?PHP

include '../../../config.php';
include '../../../headers.php';
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

$stmt = $mysqli->prepare("SELECT * From Task");

$succeed = $stmt->execute();
$result = $stmt->get_result();

$resultArray = $result->fetch_all(MYSQLI_ASSOC);
die(AppendNoErr($resultArray));
