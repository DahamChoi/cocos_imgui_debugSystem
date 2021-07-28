#include "AceHangul.h"

#include <map>
#include <unordered_map>

USING_NS_ACE;

AceHangul::AceHangul(int number)
{
    setNumber(number);
}

void AceHangul::setNumber(int number)
{
    number_ = number;
    
    if(isHangulPiece(number_))
    {
        int baseNumber = number_ - START_HANGUL;
        choseong_ = std::max((int)EMPTY, baseNumber / (JUNGSEONG_COUNT * JONGSEONG_COUNT));
        jungseong_ = std::max((int)EMPTY, (baseNumber - ((JONGSEONG_COUNT * JUNGSEONG_COUNT) * choseong_)) / JONGSEONG_COUNT);
        jongseong_ = std::max((int)JONGSEONG_EMPTY, (baseNumber - ((JONGSEONG_COUNT * JUNGSEONG_COUNT) * choseong_) - (JONGSEONG_COUNT * jungseong_)));
    }
    else
    {
        if(number >= START_PARTS_2_JAENUM && number <= END_PARTS_2_JAENUM)
        {
            jaenum_ = number - START_PARTS_2_JAENUM;
        }
        else
        {
            moenum_ = number - START_PARTS_2_MOENUM;
        }
    }
}

void AceHangul::setParts(int choseong, int jungseong, int jongseong)
{
    choseong_ = choseong;
    jungseong_ = jungseong;
    jongseong_ = jongseong;
    
    number_ = START_HANGUL;
    
    if(choseong_ != EMPTY)
    {
        number_ += JUNGSEONG_COUNT * JONGSEONG_COUNT * choseong_;
    }
    
    if(jungseong_ != EMPTY)
    {
        number_ += JONGSEONG_COUNT * jungseong_;
    }
    
    if(jongseong_ != JONGSEONG_EMPTY)
    {
        number_ += jongseong_;
    }
}

void AceHangul::setEmpty()
{
    jaenum_ = (int)EMPTY;
    moenum_ = (int)EMPTY;
    choseong_ = (int)EMPTY;
    jungseong_ = (int)EMPTY;
    jongseong_ = (int)EMPTY;
    number_ = (int)EMPTY;
}

bool AceHangul::isEmpty() const
{
    bool bEmpty = (jaenum_ == EMPTY && moenum_ == EMPTY && choseong_ == EMPTY && jungseong_ == EMPTY && jongseong_ == EMPTY && number_ == EMPTY);
    return bEmpty;
}

void AceHangul::assemble(AceHangul &left, AceHangul &right)
{
    // right가 음절인 경우
    if(isHangulPiece(right.getNumber()))
    {
        // left가 종성이 비어있지 않을 때  ex) left : 담 right : 마
        if(left.jongseong_ != JONGSEONG_EMPTY)
        {
            left.setParts(left.choseong_, left.jungseong_, JONGSEONG_EMPTY);
        }
        else
        {
            left.setParts(right.choseong_, right.jungseong_, right.jongseong_);
            right.setEmpty();
        }
    }
    //  left가 음절인 경우
    else if(isHangulPiece(left.getNumber()))
    {
        // left의 종성이 비어있고 right가 자음일 때
        if(left.jongseong_ == JONGSEONG_EMPTY && right.jaenum_ != EMPTY)
        {
            left.setParts(left.choseong_, left.jungseong_, jaenumToJongseong(right.jaenum_));
            right.setEmpty();
        }
        // left의 종성이 비어있지 않고 right가 모음일 때
        else if(left.jongseong_ != JONGSEONG_EMPTY && right.moenum_ != EMPTY)
        {
            std::pair<int, int> depress = depressJongseong(left.jongseong_);
            right.setParts(depress.second, moenumToJungseong(right.moenum_), JONGSEONG_EMPTY);
            left.setParts(left.choseong_, left.jungseong_,depress.first);
        }
        // left의 종성이 비어있고 right가 이중모음일 경우
        else if(left.jongseong_ == JONGSEONG_EMPTY && right.moenum_ != EMPTY && isDoubleMoenum(right.moenum_))
        {
            left.setParts(left.choseong_, moenumToJungseong(right.moenum_), JONGSEONG_EMPTY);
            right.setEmpty();
        }
        // left의 종성이 비어있고 right가 모음일 경우
        else if(left.jongseong_ == JONGSEONG_EMPTY && right.moenum_ != EMPTY)
        {
            int assemble = assembleJungseong(left.jungseong_, moenumToJungseong(right.moenum_));
            if(assemble != EMPTY)
            {
                left.setParts(left.choseong_, assemble, JONGSEONG_EMPTY);
                right.setEmpty();
            }
        }
        // left의 종성이 비어있지 않고 right가 자음일 때
        else if(left.jongseong_ != JONGSEONG_EMPTY && right.jaenum_ != EMPTY)
        {
            // 이중 자음 확인
            int assemble = assembleJongseong(left.jongseong_, jaenumToJongseong(right.jaenum_));
            if(assemble != EMPTY)
            {
                left.setParts(left.choseong_, left.jungseong_, assemble);
                right.setEmpty();
            }
        }
    }
    //  left가 자모인 경우
    else if(isHangulParts(left.getNumber()))
    {
        // left가 자음이고 right가 모음일 때
        if(left.jaenum_ != EMPTY && right.moenum_ != EMPTY)
        {
            left.setParts(jaenumToChoseong(left.jaenum_), moenumToJungseong(right.moenum_), JONGSEONG_EMPTY);
            right.setEmpty();
        }
    }
}

bool AceHangul::isDoubleMoenum(int moenum)
{
    bool bDoubleMoenum =
     moenum == 9  ||    //  ㅘ
     moenum == 10 ||    //  ㅙ
     moenum == 11 ||    //  ㅚ
     moenum == 14 ||    //  ㅝ
     moenum == 15 ||    //  ㅞ
     moenum == 16 ||    //  ㅟ
     moenum == 19;      //  ㅢ
    return bDoubleMoenum;
}

int AceHangul::assembleJongseong(int left, int right)
{
    std::map<std::pair<int,int>, int> assembleJongseongTable =
    {
        { {1,19}, 3 },      // ㄱㅅ
        { {4,22}, 5 },      // ㄴㅈ
        { {4,27}, 6 },      // ㄴㅎ
        { {8,1}, 9 },       // ㄹㄱ
        { {8,16}, 10 },     // ㄹㅁ
        { {8,17}, 11 },     // ㄹㅂ
        { {8,19}, 12 },     // ㄹㅅ
        { {8,25}, 13 },     // ㄹㅌ
        { {8,26}, 14 },     // ㄹㅍ
        { {8,27}, 15 },     // ㄹㅎ
        { {17,19}, 18 },    // ㅂㅅ
    };
    
    auto iter = assembleJongseongTable.find({left, right});
    return iter == assembleJongseongTable.end() ? EMPTY : iter->second;
}

std::pair<int,int> AceHangul::depressJongseong(int jongseong)
{
    std::unordered_map<int, std::pair<int,int>> depressJongseongTable =
    {
        { 3, {1,19} },      // ㄱㅅ
        { 5, {4,22} },      // ㄴㅈ
        { 6, {4,27} },      // ㄴㅎ
        { 9, {8,1} },       // ㄹㄱ
        { 10, {8,16} },     // ㄹㅁ
        { 11, {8,17} },     // ㄹㅂ
        { 12, {8,19} },     // ㄹㅅ
        { 13, {8,25} },     // ㄹㅌ
        { 14, {8,26} },     // ㄹㅍ
        { 15, {8,27} },     // ㄹㅎ
        { 18, {17,19} },    // ㅂㅅ
    };
    
    auto iter = depressJongseongTable.find(jongseong);
    if(iter == depressJongseongTable.end())
    {
        std::pair<int, int> depressResult = { JONGSEONG_EMPTY, jongseongToChoseong(jongseong) };
        return depressResult;
    }
    else
    {
        iter->second.second = jongseongToChoseong(iter->second.second);
        return iter->second;
    }
}

int AceHangul::assembleJungseong(int left, int right)
{
    std::map<std::pair<int,int>, int> assembleJungseongTable =
    {
        { {8,0}, 9  },
        { {8,1}, 10 },
        { {8,20}, 11 },
        { {13,4}, 14 },
        { {13,5}, 15 },
        { {13,20}, 16 },
        { {18,20}, 19 },
    };
    
    auto iter = assembleJungseongTable.find({left,right});
    return iter == assembleJungseongTable.end() ? EMPTY : iter->second;
}

int AceHangul::jongseongToChoseong(int jongseong)
{
    std::unordered_map<int, int> jongseongToChoseongTable =
    {
        {1,0},      //  ㄱ
        {2,1},      //  ㄲ
        {4,2},      //  ㄴ
        {7,3},      //  ㄷ
        {8,5},      //  ㄹ
        {16,6},     //  ㅁ
        {17,7},     //  ㅂ
        {19,9},     //  ㅅ
        {20,10},    //  ㅆ
        {21,11},    //  ㅇ
        {22,12},    //  ㅈ
        {23,14},    //  ㅊ
        {24,15},    //  ㅋ
        {25,16},    //  ㅌ
        {26,17},    //  ㅍ
        {27,18}     //  ㅎ
    };
    
    return jongseongToChoseongTable[jongseong];
}

int AceHangul::jaenumToChoseong(int jaenum)
{
    std::unordered_map<int, int> jaenumToChoseongTable =
    {
        {0,0},      //  ㄱ
        {1,1},      //  ㄲ
        {3,2},      //  ㄴ
        {6,3},      //  ㄷ
        {7,4},      //  ㄸ
        {8,5},      //  ㄹ
        {16,6},     //  ㅁ
        {17,7},     //  ㅂ
        {18,8},     //  ㅃ
        {20,9},     //  ㅅ
        {21,10},    //  ㅆ
        {22,11},    //  ㅇ
        {23,12},    //  ㅈ
        {24,13},    //  ㅉ
        {25,14},    //  ㅊ
        {26,15},    //  ㅋ
        {27,16},    //  ㅌ
        {28,17},    //  ㅍ
        {29,18}     //  ㅎ
    };
    
    return jaenumToChoseongTable[jaenum];
}

int AceHangul::jaenumToJongseong(int jaenum)
{
    std::unordered_map<int, int> jaenumToJongseongTable =
    {
        {0,1},      //  ㄱ
        {1,2},      //  ㄲ
        {3,4},      //  ㄴ
        {6,7},      //  ㄷ
        {8,8},      //  ㄹ
        {16,16},    //  ㅁ
        {17,17},    //  ㅂ
        {20,19},    //  ㅅ
        {21,20},    //  ㅆ
        {22,21},    //  ㅇ
        {23,22},    //  ㅈ
        {25,23},    //  ㅊ
        {26,24},    //  ㅋ
        {27,25},    //  ㅌ
        {28,26},    //  ㅍ
        {29,27}     //  ㅎ
    };
    
    return jaenumToJongseongTable[jaenum];
}

int AceHangul::jongseongToJaenum(int jongseong)
{
    std::unordered_map<int, int> jongseongToJaenumTable =
    {
        {1,0},      //  ㄱ
        {4,3},      //  ㄴ
        {7,6},      //  ㄷ
        {8,8},      //  ㄹ
        {16,16},    //  ㅁ
        {17,17},    //  ㅂ
        {19,20},    //  ㅅ
        {21,22},    //  ㅇ
        {22,23},    //  ㅈ
        {23,25},    //  ㅊ
        {24,26},    //  ㅋ
        {25,27},    //  ㅌ
        {26,28},    //  ㅍ
        {27,29}     //  ㅎ
    };
    
    return jongseongToJaenumTable[jongseong];
}

int AceHangul::moenumToJungseong(int moenum)
{
    return moenum;
}
