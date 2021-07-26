//
//  AceHangul.h
//  MPBReboot
//
//  Created by 최다함 on 2021/07/23.
//

#pragma once

#include "ace.h"

#include <string>

NS_ACE_BEGIN

class AceHangul
{
public:
    enum HANGUL_ENUM
    {
        EMPTY = -1,
        JONGSEONG_EMPTY = 0,
        START_HANGUL = 0xAC00,
        END_HANGUL = 0xD7AF,
        START_PARTS_2 = 0x3131,
        END_PARTS_2 = 0x3163,
        START_PARTS_2_JAENUM = 0x3131,
        END_PARTS_2_JAENUM = 0x314E,
        START_PARTS_2_MOENUM = 0x314F,
        END_PARTS_2_MOENUM = 0x3163,
        CHOSEONG_COUNT = 19,
        JUNGSEONG_COUNT = 21,
        JONGSEONG_COUNT = 28,
    };
    
public:
    AceHangul(int number);

public:
    static void assemble(AceHangul& left, AceHangul& right);
    
public:
    int getNumber() const { return number_; }
    int getChoseong() const { return choseong_; }
    int getJungseong() const { return jungseong_; }
    int getJongseong() const { return jongseong_; }
    
public:
    void setEmpty();
    bool isEmpty() const;
    
public:
    static bool isHangul(int number) { return isHangulPiece(number) || isHangulParts(number); }
    static bool isHangulPiece(int number){ return number >= START_HANGUL && number <= END_HANGUL; }
    static bool isHangulParts(int number) { return number >= START_PARTS_2 && number <= END_PARTS_2; }
    
private:
    static bool isDoubleMoenum(int moenum);
    static int assembleJongseong(int left, int right);
    static int assembleJungseong(int left, int right);
    static std::pair<int,int> depressJongseong(int jongseong);
    
private:
    void setNumber(int number);
    void setParts(int choseong, int jungseong, int jongseong);
    
private:
    static int jaenumToChoseong(int jaenum);
    static int jaenumToJongseong(int jaenum);
    static int jongseongToJaenum(int jongseong);
    static int moenumToJungseong(int moenum);
    static int jongseongToChoseong(int jongseong);
    
private:
    int number_;
    int jaenum_ = (int)EMPTY, moenum_ = (int)EMPTY;
    int choseong_ = (int)EMPTY, jungseong_ = (int)EMPTY, jongseong_ = (int)JONGSEONG_EMPTY;
};

NS_ACE_END
