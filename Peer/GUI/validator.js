// backend.js
.pragma library

/*
  Validate the input credential
  Return values are..
  0 - Success
  1 - credentials are empty
*/
function validateUserCredentials(uname, pword)
{
    var ret
    if(uname === "" || pword === "")
    {
        ret = 1
    }
    else
    {
        ret = 0
    }
    return ret
}

/*
  Validate the input credential to register
  Return values are..
  0 - Success
  1 - credentials are empty
  2 - passwords does not match
*/
function validateRegisterCredentials(uname, pword, pword2)
{
    var ret
    if(uname === "" || pword === "" || pword2 === "")
    {
        ret = 1
    }
    else if(pword !== pword2)
    {
        ret = 2
    }
    else
    {
        ret = 0
    }
    return ret
}
