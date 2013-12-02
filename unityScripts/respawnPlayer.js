var spawn : Transform; 
function OnTriggerEnter(other : Collider)
{
    if (other.tag == "Player")
    {
        other.transform.position = spawn.position;
    }
}