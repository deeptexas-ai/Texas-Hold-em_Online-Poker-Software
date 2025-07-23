#include "head.pb.h"
#include "hd.pb.h"
#include "cowboy.pb.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "common/macros.h"
#include "message/onclientmessage.h"
#include "logic/clientlogic/head.h"

namespace game
{
    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root)
        {
            using namespace logic;

            try
            {
                switch(static_cast<unsigned int>(eMSG))
                {
                // 牌局快照
                case XGameCBProto::E_CB_msg2csGameStation_E:
                {
                    clientlogic::GameStation(uid, vecMsgData, root);
                }
                break;
                // 玩家坐下
                case XGameCBProto::E_CB_msg2csSit_E:
                {
                    clientlogic::Sit(uid, vecMsgData, root);
                }
                break;     
                // 补充筹码
                case XGameCBProto::E_CB_msg2csBuyChip_E:
                {
                    clientlogic::BuyChip(uid, vecMsgData, root);
                }
                break;
                // 下注
                case XGameCBProto::E_CB_msg2csTokenBet_E:
                {
                    clientlogic::TokenBet(uid, vecMsgData, root);
                }
                break;
                // 倍投下注
                case XGameCBProto::E_CB_msg2csDoubleTokenBet_E:
                {
                    clientlogic::DoubleTokenBet(uid, vecMsgData, root);
                }
                break;
                // 复投下注
                case XGameCBProto::E_CB_msg2csRepeatTokenBet_E:
                {
                    clientlogic::RepeatTokenBet(uid, vecMsgData, root);
                }
                break;
                // 走势图
                case XGameCBProto::E_CB_msg2csWinData_E:
                {
                    clientlogic::WinCowBoy(uid, vecMsgData, root);
                }
                break;
                // 牌局统计
                case XGameCBProto::E_CB_msg2csWinRecord_E:
                {
                    clientlogic::WinRecord(uid, vecMsgData, root);
                }
                break;
                case XGameHDProto::HD_msg2sCheckBegin_E:
                {
                    clientlogic::TestBegin(uid, vecMsgData, root);
                }
                break;
                case XGameHDProto::HD_msg2csGameInfo_E:
                case XGameHDProto::HD_msg2csWatchInfo_E:
                {
                    clientlogic::SomeInfo(uid, vecMsgData, root, static_cast<unsigned char>(eMSG));
                }
                break;
                case XGameHDProto::HD_msg2csStand_E:
                case XGameHDProto::HD_msg2csSit_E:
                {
                    clientlogic::SomeAct(uid, vecMsgData, root, static_cast<unsigned char>(eMSG));
                }
                break;
                //
                default:
                {
                    LOG_ERROR("undefined network message from remote user, uid : " << uid << ", eMSG: " << eMSG);
                }
                break;
                }
            }
            catch (const TarsDecodeException &e)
            {
                ERROR(string("catch tars decode exception : ") + e.what());
            }
            catch (const TarsEncodeException &e)
            {
                ERROR(string("catch tars encode exception : ") + e.what());
            }
            catch (const TarsProtoException &e)
            {
                ERROR(string("catch proto exception : ") + e.what());
            }
            catch (const TC_Exception &e)
            {
                ERROR(string("catch tc exception : ") + e.what());
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            }
        }
    };
};


