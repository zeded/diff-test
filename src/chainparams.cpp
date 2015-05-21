// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x42;
        pchMessageStart[2] = 0x13;
        pchMessageStart[3] = 0x09;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 15814;
        nRPCPort = 15815;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=1312314, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1420323277, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "2015, January, 30, WSJ: Qatar Airways Buys $1.7 billion Stake in British Airways Operator";
        CTransaction txNew;
        txNew.nTime = 1422632991;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1422632991;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 773726;
 //uncomment to log genesis block info
//      //  start
//        if (true && genesis.GetHash() != hashGenesisBlock)
//                       {
//                           printf("Searching for genesis block...\n");
//                           uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
//                           uint256 thash;
//
//                           while (true)
//                           {
//                               thash = genesis.GetHash();
//                               if (thash <= hashTarget)
//                                   break;
//                               if ((genesis.nNonce & 0xFFF) == 0)
//                               {
//                                   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
//                               }
//                               ++genesis.nNonce;
//                               if (genesis.nNonce == 0)
//                               {
//                                   printf("NONCE WRAPPED, incrementing time\n");
//                                   ++genesis.nTime;
//                               }
//                           }
//                           printf("genesis.nTime = %u \n", genesis.nTime);
//                           printf("genesis.nNonce = %u \n", genesis.nNonce);
//                           printf("genesis.nVersion = %u \n", genesis.nVersion);
//                           printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root
//                           printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
//
//                       }
//
//        //end

       // genesis.nTime = 1422632991
       // genesis.nNonce = 773726
       // genesis.nVersion = 1
       // genesis.hashMerkleRoot = 4090e080fc43311842d9f4fae900d4de9dcbae0eb326a7a8bb2b3ef409f3b304
       // genesis.GetHash = 000008764d5c635c287151cabaa066526f6aac5ac885b46f4183f8c1b7c357d4

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000008764d5c635c287151cabaa066526f6aac5ac885b46f4183f8c1b7c357d4"));
        assert(genesis.hashMerkleRoot == uint256("0x4090e080fc43311842d9f4fae900d4de9dcbae0eb326a7a8bb2b3ef409f3b304"));

        vSeeds.push_back(CDNSSeedData("198.105.125.83", "198.105.125.83"));
        vSeeds.push_back(CDNSSeedData("198.105.122.107", "198.105.122.107"));
        vSeeds.push_back(CDNSSeedData("198.105.125.84", "198.105.125.84"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(25);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(8);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbc;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xb0;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 25814;
        nRPCPort = 25815;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 54520;
//uncomment to log genesis block info

          //if (true && genesis.GetHash() != hashGenesisBlock)
        //                 {
      //                       printf("Searching for genesis block...\n");
    //                         uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
  //                           uint256 thash;
//
                      //       while (true)
                    //         {
                  //               thash = genesis.GetHash();
                //                 if (thash <= hashTarget)
              //                       break;
            //                     if ((genesis.nNonce & 0xFFF) == 0)
          //                       {
        //                             printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
      //                           }
    //                             ++genesis.nNonce;
  //                               if (genesis.nNonce == 0)
//                                 {
//                                     printf("NONCE WRAPPED, incrementing time\n");
//                                     ++genesis.nTime;
//                                }
//                             }
//                             printf("genesis.nTime = %u \n", genesis.nTime);
//                             printf("genesis.nNonce = %u \n", genesis.nNonce);
//                             printf("genesis.nVersion = %u \n", genesis.nVersion);
//                             printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
//                             printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
//
//                         }
//
//
        //genesis.nTime = 1422632991
        //genesis.nNonce = 54520
        //genesis.nVersion = 1
        //genesis.hashMerkleRoot = 4090e080fc43311842d9f4fae900d4de9dcbae0eb326a7a8bb2b3ef409f3b304
        //genesis.GetHash = 0000bc53a50f95a98dd38be1ea73577e73f6232ad6483c213575a589ae32f8a0

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000bc53a50f95a98dd38be1ea73577e73f6232ad6483c213575a589ae32f8a0"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xad;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1422632991;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
//uncomment to log regtest genesis block info

        //if (true)
        //                 {
      //                       printf("Searching for genesis block...\n");
    //                         uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
  //                           uint256 thash;
//
              //               while (true)
            //                 {
          //                       thash = genesis.GetHash();
        //                         if (thash <= hashTarget)
                                  //   break;
                                // if ((genesis.nNonce & 0xFFF) == 0)
                              //   {
                            //         printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                          //       }
                        //         ++genesis.nNonce;
                      //           if (genesis.nNonce == 0)
                    //             {
                  //                   printf("NONCE WRAPPED, incrementing time\n");
                //                     ++genesis.nTime;
              //                   }
            //                 }
          //                   printf("genesis.nTime = %u \n", genesis.nTime);
        //                     printf("genesis.nNonce = %u \n", genesis.nNonce);
      //                       printf("genesis.nVersion = %u \n", genesis.nVersion);
    //                         printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
  //                           printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
//
       //                  }

        //genesis.nTime = 1422632991
        //genesis.nNonce = 3
        //genesis.nVersion = 1
        //genesis.hashMerkleRoot = 4090e080fc43311842d9f4fae900d4de9dcbae0eb326a7a8bb2b3ef409f3b304
        //genesis.GetHash = 260043ac5d11e60031adc2444b81a079be69531c536d9f6f2b7551773e2dbc4f

        assert(hashGenesisBlock == uint256("0x260043ac5d11e60031adc2444b81a079be69531c536d9f6f2b7551773e2dbc4f"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
