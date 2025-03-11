#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

class CBank
{
public:
	explicit CBank(Money cash);

	CBank(const CBank&) = delete;
	CBank& operator=(const CBank&) = delete;

	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] Money GetCash() const noexcept;
	[[nodiscard]] Money GetAccountBalance(AccountId accountId) const;
	void WithdrawMoney(AccountId accountId, Money amount);
	[[nodiscard]] bool TryWithdrawMoney(AccountId accountId, Money amount);
	void DepositMoney(AccountId accountId, Money amount);
	[[nodiscard]] AccountId OpenAccount();
	[[nodiscard]] Money CloseAccount(AccountId accountId);

private:
	static void ValidateAmount(Money amount);

	[[nodiscard]] std::unordered_map<AccountId, Money>::iterator GetAccount(AccountId accountId);
	[[nodiscard]] std::unordered_map<AccountId, Money>::const_iterator GetAccount(AccountId accountId) const;
	[[nodiscard]] AccountId GetNewAccountId() noexcept;

	Money m_cash;
	std::unordered_map<AccountId, Money> m_accounts;
	AccountId m_nextAccountId = 1;
};
