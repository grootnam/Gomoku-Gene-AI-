using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
public class Gomoku : MonoBehaviour
{
    [DllImport("GomokuDLL")]
    public static extern void Init();
    [DllImport("GomokuDLL")]
    public static extern bool IsWin(int mid,int x,int y);
    [DllImport("GomokuDLL")]
    public static extern bool SetBlackStone(int x,int y);
    [DllImport("GomokuDLL")]
    public static extern void FrameMove(ref float x, ref float y);
    [DllImport("GomokuDLL")]
    public static extern void Release();

    public GameObject m_BlackStone;
    public GameObject m_WhiteStone;
    int GameFrame;
    // Start is called before the first frame update
    void Start()
    {
        Init();
        GameFrame =0;
    }
    void ReSetGame()
    {
        for(int i=0;i<gameObject.transform.childCount;i++)
        {
            Destroy(gameObject.transform.GetChild(i).gameObject);
        }
        Release();
        Init();
        GameFrame=0;
        Debug.Log("게임 재시작!");
    }
    void BlackStoneFrameMove()
    {
        if (m_BlackStone!=null)
        {
            if(Input.GetMouseButtonUp(0))
            {
                float x =Input.mousePosition.x/250.0f-1.0f;
                float y = Input.mousePosition.y/250.0f-1.0f;
                float dx=Mathf.Round(x*10)*0.1f;
                float dy=Mathf.Round(y*10)*0.1f;

                int ix = (int)Mathf.Round(dx*10.0f+10.0f);
                int iy = (int)Mathf.Round(10.0f - (dx*10.0f));
                if(SetBlackStone(ix,iy)==true){
                    GameObject stone = GameObject.Instantiate(m_BlackStone);
                    stone.transform.parent=this.transform;
                    stone.transform.position = new Vector3(dx,0,dy);
                    GameFrame++;
                    if(IsWin(2,ix,iy)==true)
                    {
                        Debug.Log("흑돌이 이겼습니다!");
                        ReSetGame();
                    }
                    else
                    {
                      Debug.Log("잘못 두었습니다! 다시주세요!");
                    }
                    
                }
                
            }
            
        }
    }
    void WhiteStoneFrameMove(){
        if(m_WhiteStone!=null)
        {
            Vector2 wp = new Vector2();
            FrameMove(ref wp.x,ref wp.y);

            float dx=(wp.x /10.0f - 1.0f);
            float dy=(1.0f - (wp.y / 10.0f));
            GameObject stone = GameObject.Instantiate(m_WhiteStone);
            stone.transform.parent=this.transform;
            stone.transform.position = new Vector3(dx,0,dy);
            GameFrame++;
            if(IsWin(1,(int)wp.x,(int)wp.y)==true)
            {
                Debug.Log("백돌이 이겼습니다!");
                ReSetGame();
            }
        }
    }
    // Update is called once per frame
    void Update()
    {
        if(GameFrame%2==0)
        {
            BlackStoneFrameMove();
        }
        else
        {
            WhiteStoneFrameMove();
        }
    }
    void OnApplicationQuit()
    {
        Release();
    }
}
