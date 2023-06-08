<?PHP
include "../../../config.php";
include '../../../utility.php';
include '../../../database.php';
include '../../../ensured_login.php';

#update will change things that are in here

if (!isset($_POST['title']) || !isset($_POST['details']) || !isset($_POST['authorID']) ||  !isset($_POST['cost']) ||!isset($_POST['digital']) || !isset($_POST['task_ID']))
{
    die(ReturnError(3,"Incorrect Parameters"));
}
# vars go here
# active will always be set to true, given that the task has just been created
$task_ID    = $_POST['task_ID'];
$title      = $_POST['title'];
$active     = 1;
$details    = $_POST['details'];
$authorID   = $GLOBALS['myID'];
$digital    = $_POST['digital'];
$cost	    = $_POST['cost'];


$succeed = false;

#To test, Change to _GET


if (!$digital)
{
    if (!isset($_POST['address']) || !isset($_POST['city']) || !isset($_POST['state']) ||  !isset($_POST['zipcode']))
    {
        die(ReturnError(3,"Incorrect Parameters"));
    }
    
    # vars go here as well
    $address    =  $_POST['address'];
    $city       =  $_POST['city'];
    $state      = $_POST['state'];
    $zipcode    = $_POST['zipcode'];
    
    // Update 
    $stmt =  $mysqli->prepare("UPDATE `Task` Set `Title` = ?, `Active` = ?, `Details` = ?, `Author_ID_FK` = ?, `Cost` = ?, `Digital` = ?, `Address` = ?, `City` = ? , `State` = ?, `Zipcode` = ? WHERE `Task_ID` = ? ");
    
    //printf("Error message: %s\n", $mysqli->error);

    $stmt->bind_param("sisidisssii", $title, $active, $details, $authorID, $cost, $digital, $address, $city, $state, $zipcode, $task_ID);
    $succeed = $stmt->execute();
}
else
{
    // Insert 
    $stmt =  $mysqli->prepare("UPDATE `Task` Set `Title` = ?, `Active` = ?, `Details` = ?, `Author_ID_FK` = ?, `Cost` = ?, `Digital` = ? WHERE `Task_ID` = ?;");
    $stmt->bind_param("sisidii", $title, $active, $details, $authorID, $cost, $digital, $task_ID);
    $succeed = $stmt->execute();
}

#printf("Error message: %s\n", $mysqli->error);

if ($succeed)
{
    die(NoErr());
}
die(ReturnError(2,"Unexpected Unknown Error"));
