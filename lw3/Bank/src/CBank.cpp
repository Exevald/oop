#include "CBank.h"

CBank::CBank(Money cash)
	: m_cash(cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Initial cash can't be less than 0");
	}
}

void CBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidateAmount(amount);
	auto srcAccount = GetAccount(srcAccountId);
	auto dstAccount = GetAccount(dstAccountId);

	if (srcAccount->second < amount)
	{
		throw BankOperationError("Insufficient funds in source account: " + std::to_string(srcAccountId));
	}

	srcAccount->second -= amount;
	dstAccount->second += amount;
}

bool CBank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidateAmount(amount);
	auto srcAccount = GetAccount(srcAccountId);
	auto dstAccount = GetAccount(dstAccountId);

	if (srcAccount->second < amount)
	{
		return false;
	}

	srcAccount->second -= amount;
	dstAccount->second += amount;
	return true;
}

Money CBank::GetCash() const noexcept
{
	return m_cash;
}

Money CBank::GetAccountBalance(AccountId accountId) const
{
	return GetAccount(accountId)->second;
}

void CBank::WithdrawMoney(AccountId accountId, Money amount)
{
	ValidateAmount(amount);
	auto account = GetAccount(accountId);

	if (account->second < amount)
	{
		throw BankOperationError("Insufficient funds in account: " + std::to_string(accountId));
	}

	account->second -= amount;
	m_cash += amount;
}

bool CBank::TryWithdrawMoney(AccountId accountId, Money amount)
{
	ValidateAmount(amount);
	auto account = GetAccount(accountId);

	if (account->second < amount)
	{
		return false;
	}

	account->second -= amount;
	m_cash += amount;
	return true;
}

void CBank::DepositMoney(AccountId accountId, Money amount)
{
	ValidateAmount(amount);
	auto account = GetAccount(accountId);

	if (m_cash < amount)
	{
		throw BankOperationError("Insufficient cash in bank");
	}

	m_cash -= amount;
	account->second += amount;
}

AccountId CBank::OpenAccount()
{
	auto newId = GetNewAccountId();
	m_accounts.emplace(newId, 0);
	return newId;
}

Money CBank::CloseAccount(AccountId accountId)
{
	auto account = GetAccount(accountId);
	Money balance = account->second;
	m_accounts.erase(accountId);
	m_cash += balance;

	return balance;
}

void CBank::ValidateAmount(Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("Amount can't be negative");
	}
}

std::unordered_map<AccountId, Money>::iterator CBank::GetAccount(AccountId accountId)
{
	auto account = m_accounts.find(accountId);
	if (account == m_accounts.end())
	{
		throw BankOperationError("Account not found: " + std::to_string(accountId));
	}
	return account;
}

std::unordered_map<AccountId, Money>::const_iterator CBank::GetAccount(AccountId accountId) const
{
	auto account = m_accounts.find(accountId);
	if (account == m_accounts.end())
	{
		throw BankOperationError("Account not found: " + std::to_string(accountId));
	}
	return account;
}

AccountId CBank::GetNewAccountId() noexcept
{
	return m_nextAccountId++;
}