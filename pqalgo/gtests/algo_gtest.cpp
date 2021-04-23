#include <string>

#include <pqalgo/lru.h>
#include <pqalgo/kmp.h>
#include <pqalgo/trie.h>

#include "gtest/gtest.h"

class CAlgoTest : public ::testing::Test
{
protected:
    CAlgoTest() {}
    ~CAlgoTest() override {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(CAlgoTest, TestKmp)
{
    std::string s = "12 345 6789 0", p = "789";

    int idx1 = pqalgo::bf(s.c_str(), p.c_str());
    int idx2 = pqalgo::kmp(s.c_str(), p.c_str());

    EXPECT_STREQ(p.c_str(), s.substr(idx1, p.length()).c_str());
    EXPECT_STREQ(p.c_str(), s.substr(idx2, p.length()).c_str());
}

TEST_F(CAlgoTest, TestTrie)
{
    pqalgo::Trie trie;

    trie.insert("my");
    trie.insert("mydb");
    trie.insert("mysql");

    EXPECT_FALSE(trie.find("milk"));
    EXPECT_TRUE(trie.find("mysql"));

    EXPECT_FALSE(trie.startsWith("mike"));
    EXPECT_TRUE(trie.startsWith("my"));
}

TEST_F(CAlgoTest, TestLRU)
{
    pqalgo::LRU<int, int> lru(5);

    lru[1] = 1;
    lru[3] = 3;
    lru[5] = 5;
    lru[7] = 7;
    lru[9] = 9;

    EXPECT_EQ(lru.front().first, 9);
    EXPECT_EQ(lru.back().first, 1);

    lru[6] = 6;

    EXPECT_EQ(lru.front().first, 6);
    EXPECT_EQ(lru.back().first, 3);
}
