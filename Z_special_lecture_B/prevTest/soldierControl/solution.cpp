struct NODE {
    int id;
    int version;
    NODE* nxt;
    // mScore, mTeam 에 대한 정보는 따로 배열이 있음
    NODE() {}
    NODE(int id, int v): id(id), version(v), nxt(nullptr) {}
    NODE(int id, int v, NODE* ptr) : id(id), version(v), nxt(ptr) {}
} soldier[200001];

int cnt;
int version[100001];
int whichTeam[100001];

NODE* makeNODE(int id, NODE* ptr = nullptr) {
    NODE* ret = &soldier[cnt++];
    ret->id = id;
    ret->nxt = ptr;
    ret->version = ++version[id];
    // updateSoldier 에서 lazy 하게 처리하기 위해 version 을 ++ 해가면 됨
    return ret;
}

struct TEAM {
    // 5개의 팀에 대해서 각각 5개 점수에 대한 그룹이 있음
    NODE* head[6];
    NODE* tail[6];
} team[6];

void init()
{
    cnt = 0;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            team[i].head[j] = team[i].tail[j] = makeNODE(0); // dummy NODE
        }
    }
    
    for (int i = 0; i < 100001; ++i) {
        version[i] = 0;
        whichTeam[i] = 0;
    }
}

void hire(int mID, int mTeam, int mScore)
{
    NODE* newNODE = makeNODE(mID);
    team[mTeam].tail[mScore]->nxt = newNODE;
    team[mTeam].tail[mScore] = newNODE;
    whichTeam[mID] = mTeam;
}

void fire(int mID)
{
    version[mID] = -1;
}

void updateSoldier(int mID, int mScore)
{
    hire(mID, whichTeam[mID], mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore >= 0) {
        for (int i = 5; i >= 1; --i) {
            int nextScore = i + mChangeScore;
            if (nextScore > 5) nextScore = 5;
            if (i == nextScore) continue;
            if (team[mTeam].head[i]->nxt == nullptr) continue;
            
            team[mTeam].tail[nextScore]->nxt = team[mTeam].head[i]->nxt;
            team[mTeam].tail[nextScore] = team[mTeam].tail[i];
            team[mTeam].head[i]->nxt = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
    }
    
    if (mChangeScore < 0) {
        for (int i = 1; i <= 5; ++i) {
            int nextScore = i + mChangeScore;
            if (nextScore < 1) nextScore = 1;
            if (i == nextScore) continue;
            if (team[mTeam].head[i]->nxt == nullptr) continue;
            
            team[mTeam].tail[nextScore]->nxt = team[mTeam].head[i]->nxt;
            team[mTeam].tail[nextScore] = team[mTeam].tail[i];
            team[mTeam].head[i]->nxt = nullptr;
            team[mTeam].tail[i] = team[mTeam].head[i];
        }
    }
}

int bestSoldier(int mTeam)
{
    for (int i = 5; i >= 1; --i) {
        int largestID = 0;
        NODE* now = team[mTeam].head[i]->nxt;
        if (now == nullptr) continue;
        
        while(now != nullptr) {
            if (now->version == version[now->id]) {
                if (now->id > largestID) largestID = now->id;
            }
            now = now->nxt;
        }
        if (largestID != 0) return largestID;
    }
    return 0;
}
