#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
    waiting.clear();
}

EnemyManager::~EnemyManager()
{
}

bool EnemyManager::CanAttack(Golem* golem)
{
    // 一番正しい書き方
    //for (std::list<Golem*>::iterator itr = waiting.begin();
    //    itr != waiting.end(); itr++) {
    //    Golem* g = *itr;
    //}
    // 型を書きたくない
    //for (auto itr = waiting.begin(); 
    //                        itr != waiting.end(); itr++) {
    //    Golem* g = *itr;
    //}
    // さらに楽する
    bool found = false;
    for (Golem* g : waiting) {
        if (g == golem) {
            found = true;
        }
    }
    if (not found) {
        waiting.push_back(golem); // 最後に追加
    }
    return *(waiting.begin()) == golem;

    // 補足
    int m[10];
    for (int d : m) { // この時dはmのデータのコピー
        d = 0; // mは0にできない
    }
    for (int& d : m) { // この時dはmのデータの参照
        d = 0; // mの配列を0にできる
    }
}

void EnemyManager::CancelAttack(Golem* golem)
{
    waiting.remove(golem);
}
