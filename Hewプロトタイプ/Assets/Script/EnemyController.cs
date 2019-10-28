using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    Transform Player1;
    Transform Player2;
    Transform Enemy;
    public bool deadflag;
    public bool spflag;
    public bool active;
    // Start is called before the first frame update
    void Start()
    {
        Player1 = GameObject.Find("Player1").transform;
        Player2 = GameObject.Find("Player2").transform;
        Enemy = this.gameObject.transform;
        deadflag = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (deadflag)
        {
            Enemy.rotation = Quaternion.AngleAxis(90, Vector3.forward);
            Enemy.position -= Vector3.up * 0.1f;
            Destroy(this.gameObject, 1.5f);
        }
        else
        {
            if (spflag)
            {
                if (active)
                {
                    float dif = Vector3.Distance(Enemy.position, Player1.position) - Vector3.Distance(Enemy.position, Player2.position);
                    Enemy.position = Vector3.MoveTowards(Enemy.position, dif < 0 ? Player1.position : Player2.position, 0.05f);
                    Enemy.Rotate(new Vector3(0,10.0f,0));
                }
                else
                {
                    float dis = Mathf.Min(Vector3.Distance(Enemy.position, Player1.position), Vector3.Distance(Enemy.position, Player2.position));
                    if (dis < 30)
                    {
                        active = true;
                    }
                }
            }

            else
            {

                if (active)
                {
                    float dif = Vector3.Distance(Enemy.position, Player1.position) - Vector3.Distance(Enemy.position, Player2.position);
                    Enemy.position = Vector3.MoveTowards(Enemy.position, dif < 0 ? Player1.position : Player2.position, 0.1f);
                    Enemy.rotation = Quaternion.LookRotation(dif < 0 ? Player1.position - Enemy.position : Player2.position - Enemy.position);
                }
                else
                {
                    float dis = Mathf.Min(Vector3.Distance(Enemy.position, Player1.position), Vector3.Distance(Enemy.position, Player2.position));
                    if (dis < 30)
                    {
                        active = true;
                    }
                }

            }
        }
    }
}
