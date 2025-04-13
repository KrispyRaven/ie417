class BankAccount:
    """
    A simple bank account class to manage deposits and withdrawals.

    :param owner: The name of the account owner.
    :type owner: str
    :param balance: Initial account balance (default is 0.0).
    :type balance: float
    """

    def __init__(self, owner: str, balance: float = 0.0):
        self.owner = owner
        self.balance = balance

    def deposit(self, amount: float) -> None:
        """
        Deposit money into the account.

        :param amount: Amount of money to deposit.
        :type amount: float
        :raises ValueError: If the deposit amount is not positive.
        """
        if amount <= 0:
            raise ValueError("Deposit amount must be positive.")
        self.balance += amount

    def withdraw(self, amount: float) -> None:
        """
        Withdraw money from the account.

        :param amount: Amount of money to withdraw.
        :type amount: float
        :raises ValueError: If the withdrawal amount is greater than the current balance or not positive.
        """
        if amount <= 0:
            raise ValueError("Withdrawal amount must be positive.")
        if amount > self.balance:
            raise ValueError("Insufficient funds.")
        self.balance -= amount

    def get_balance(self) -> float:
        """
        Get the current balance of the account.

        :return: Current account balance.
        :rtype: float
        """
        return self.balance

    def __str__(self) -> str:
        """
        Return a string representation of the account.

        :return: String with owner and balance.
        :rtype: str
        """
        return f"BankAccount(owner='{self.owner}', balance={self.balance:.2f})"
