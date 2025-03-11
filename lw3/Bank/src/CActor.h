#pragma once

#include "CBank.h"
#include <iostream>
#include <memory>
#include <string>

class CActor;
class CActorWithBankAccount;

struct Actors
{
	CActorWithBankAccount* homer;
	CActorWithBankAccount* marge;
	CActor* bart;
	CActor* lisa;
	CActorWithBankAccount* apu;
	CActorWithBankAccount* mrBurns;
	CActor* nelson;
	CActorWithBankAccount* snake;
	CActorWithBankAccount* smithers;
};

class CActor
{
public:
	explicit CActor(Money cash)
		: m_cash(cash)
	{
		if (cash < 0)
		{
			throw std::out_of_range("Initial cash can't be negative");
		}
	}

	[[nodiscard]] Money GetCash() const
	{
		return m_cash;
	}

	[[nodiscard]] bool SendCash(CActor& recipient, Money amount)
	{
		if (m_cash < amount)
		{
			return false;
		}
		m_cash -= amount;
		recipient.AddCash(amount);
		return true;
	}

	[[nodiscard]] bool StealCash(CActor& victim, Money amount)
	{
		return victim.SendCash(*this, amount);
	}

	virtual void Act(Actors& actors) = 0;

	virtual ~CActor() = default;

protected:
	void AddCash(Money amount)
	{
		m_cash += amount;
	}

	bool SpendCash(Money amount)
	{
		if (m_cash < amount)
		{
			return false;
		}
		m_cash -= amount;
		return true;
	}

private:
	Money m_cash;
};

class CActorWithBankAccount : public CActor
{
public:
	CActorWithBankAccount(Money cash, AccountId accountId, CBank& bank)
		: CActor(cash)
		, m_accountId(accountId)
		, m_bank(bank)
	{
		CActorWithBankAccount::DepositMoney(cash);
	}

	[[nodiscard]] Money GetAccountBalance() const
	{
		return m_bank.GetAccountBalance(m_accountId);
	}

	[[nodiscard]] AccountId GetAccountId() const
	{
		return m_accountId;
	}

	[[nodiscard]] bool SendMoney(AccountId dstAccountId, Money amount)
	{
		return m_bank.TrySendMoney(m_accountId, dstAccountId, amount);
	}

	[[nodiscard]] bool StealMoney(AccountId victimAccountId, Money amount)
	{
		return m_bank.TrySendMoney(victimAccountId, m_accountId, amount);
	}

	[[nodiscard]] bool WithdrawMoney(Money amount)
	{
		if (m_bank.TryWithdrawMoney(m_accountId, amount))
		{
			AddCash(amount);
			return true;
		}
		return false;
	}

	bool DepositMoney(Money amount)
	{
		if (SpendCash(amount))
		{
			m_bank.DepositMoney(m_accountId, amount);
			return true;
		}
		return false;
	}

	[[nodiscard]] Money CloseAccount()
	{
		Money balance = m_bank.CloseAccount(m_accountId);
		AddCash(balance);
		return balance;
	}

	void OpenAccount()
	{
		m_accountId = m_bank.OpenAccount();
	}

private:
	AccountId m_accountId;
	CBank& m_bank;
};