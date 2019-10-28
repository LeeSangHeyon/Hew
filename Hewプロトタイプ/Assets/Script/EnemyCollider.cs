using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCollider : MonoBehaviour
{
    // Start is called before the first frame update

    void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.CompareTag("Enemy"))
        {
            other.gameObject.GetComponent<EnemyController>().deadflag = true;
            other.gameObject.GetComponent<Rigidbody>().isKinematic = true;
            if(this.gameObject.CompareTag("Arrow"))
            {
                this.gameObject.GetComponent<Rigidbody>().isKinematic = true;
            }
            Debug.Log("当たった!");
        }
           
    }
}
