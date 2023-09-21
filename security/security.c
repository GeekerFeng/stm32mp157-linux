#define EARLY_LSM_COUNT (__end_early_lsm_info - __start_early_lsm_info)
struct security_hook_heads security_hook_heads __lsm_ro_after_init;
static struct lsm_blob_sizes blob_sizes __lsm_ro_after_init;
static __initconst const char * const builtin_lsm_order = CONFIG_LSM;
	init_debug("%s ordering: %s (%sabled)\n", from, lsm->name,
		   is_enabled(lsm) ? "en" : "dis");
	if (*need > 0) {
		offset = *lbs;
		*lbs += *need;
		*need = offset;
	}
			init_debug("exclusive chosen: %s\n", lsm->name);
			append_ordered_lsm(lsm, "first");
				init_debug("security=%s disabled: %s\n",
			if (lsm->order == LSM_ORDER_MUTABLE &&
			    strcmp(lsm->name, name) == 0) {
				append_ordered_lsm(lsm, origin);
			init_debug("%s ignored: %s\n", origin, name);
		init_debug("%s disabled: %s\n", origin, lsm->name);
				GFP_KERNEL);
			pr_info("security= is ignored because it is superseded by lsm=\n");
	init_debug("cred blob size     = %d\n", blob_sizes.lbs_cred);
	init_debug("file blob size     = %d\n", blob_sizes.lbs_file);
	init_debug("inode blob size    = %d\n", blob_sizes.lbs_inode);
	init_debug("ipc blob size      = %d\n", blob_sizes.lbs_ipc);
	init_debug("msg_msg blob size  = %d\n", blob_sizes.lbs_msg_msg);
	init_debug("task blob size     = %d\n", blob_sizes.lbs_task);
	int i;
	struct hlist_head *list = (struct hlist_head *) &security_hook_heads;
	for (i = 0; i < sizeof(security_hook_heads) / sizeof(struct hlist_head);
	     i++)
		INIT_HLIST_HEAD(&list[i]);
	pr_info("Security Framework initializing\n");
				char *lsm)
int security_binder_set_context_mgr(struct task_struct *mgr)
int security_binder_transaction(struct task_struct *from,
				struct task_struct *to)
int security_binder_transfer_binder(struct task_struct *from,
				    struct task_struct *to)
int security_binder_transfer_file(struct task_struct *from,
				  struct task_struct *to, struct file *file)
		     kernel_cap_t *effective,
		     kernel_cap_t *inheritable,
		     kernel_cap_t *permitted)
				effective, inheritable, permitted);
				effective, inheritable, permitted);
int security_bprm_set_creds(struct linux_binprm *bprm)
	return call_int_hook(bprm_set_creds, 0, bprm);
int security_fs_context_parse_param(struct fs_context *fc, struct fs_parameter *param)
	return call_int_hook(fs_context_parse_param, -ENOPARAM, fc, param);
	return call_int_hook(sb_alloc_security, 0, sb);
                       const char *type, unsigned long flags, void *data)
int security_sb_pivotroot(const struct path *old_path, const struct path *new_path)
				void *mnt_opts,
				unsigned long kern_flags,
				unsigned long *set_kern_flags)
				mnt_opts ? -EOPNOTSUPP : 0, sb,
				mnt_opts, kern_flags, set_kern_flags);
				struct super_block *newsb,
				unsigned long kern_flags,
				unsigned long *set_kern_flags)
				kern_flags, set_kern_flags);
int security_add_mnt_opt(const char *option, const char *val, int len,
			 void **mnt_opts)
{
	return call_int_hook(sb_add_mnt_opt, -EINVAL,
					option, val, len, mnt_opts);
}
EXPORT_SYMBOL(security_add_mnt_opt);

int security_move_mount(const struct path *from_path, const struct path *to_path)
				unsigned int obj_type)
				inode_free_by_rcu);
					const struct qstr *name, void **ctx,
					u32 *ctxlen)
	return call_int_hook(dentry_init_security, -EOPNOTSUPP, dentry, mode,
				name, ctx, ctxlen);
				name, old, new);
						&lsm_xattr->name,
						&lsm_xattr->value,
						&lsm_xattr->value_len);
int security_old_inode_init_security(struct inode *inode, struct inode *dir,
				     const struct qstr *qstr, const char **name,
				     void **value, size_t *len)
	if (unlikely(IS_PRIVATE(inode)))
		return -EOPNOTSUPP;
	return call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir,
			     qstr, name, value, len);
EXPORT_SYMBOL(security_old_inode_init_security);
int security_path_mknod(const struct path *dir, struct dentry *dentry, umode_t mode,
			unsigned int dev)
int security_path_mkdir(const struct path *dir, struct dentry *dentry, umode_t mode)
		     (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
	if (flags & RENAME_EXCHANGE) {
		int err = call_int_hook(path_rename, 0, new_dir, new_dentry,
					old_dir, old_dentry);
		if (err)
			return err;
	}

				new_dentry);
#endif
int security_inode_create(struct inode *dir, struct dentry *dentry, umode_t mode)
			 struct dentry *new_dentry)
			    const char *old_name)
int security_inode_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
			   struct inode *new_dir, struct dentry *new_dentry,
			   unsigned int flags)
        if (unlikely(IS_PRIVATE(d_backing_inode(old_dentry)) ||
            (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
						     old_dir, old_dentry);
					   new_dir, new_dentry);
int security_inode_setattr(struct dentry *dentry, struct iattr *attr)
	return evm_inode_setattr(dentry, attr);
int security_inode_setxattr(struct dentry *dentry, const char *name,
	ret = call_int_hook(inode_setxattr, 1, dentry, name, value, size,
				flags);
	return evm_inode_setxattr(dentry, name, value, size);
int security_inode_removexattr(struct dentry *dentry, const char *name)
	ret = call_int_hook(inode_removexattr, 1, dentry, name);
		ret = cap_inode_removexattr(dentry, name);
	return evm_inode_removexattr(dentry, name);
int security_inode_killpriv(struct dentry *dentry)
	return call_int_hook(inode_killpriv, 0, dentry);
int security_inode_getsecurity(struct inode *inode, const char *name, void **buffer, bool alloc)
		return -EOPNOTSUPP;
		rc = hp->hook.inode_getsecurity(inode, name, buffer, alloc);
		if (rc != -EOPNOTSUPP)
	return -EOPNOTSUPP;
int security_inode_setsecurity(struct inode *inode, const char *name, const void *value, size_t size, int flags)
		return -EOPNOTSUPP;
								flags);
		if (rc != -EOPNOTSUPP)
	return -EOPNOTSUPP;
int security_inode_listsecurity(struct inode *inode, char *buffer, size_t buffer_size)
	return call_int_hook(inode_copy_up_xattr, -EOPNOTSUPP, name);
			unsigned long flags)
	ret = call_int_hook(mmap_file, 0, file, prot,
					mmap_prot(file, prot), flags);
	return ima_file_mmap(file, prot);
			    unsigned long prot)
	return call_int_hook(file_mprotect, 0, vma, reqprot, prot);
				  struct fown_struct *fown, int sig)
int security_kernel_read_file(struct file *file, enum kernel_read_file_id id)
	ret = call_int_hook(kernel_read_file, 0, file, id);
	return ima_read_file(file, id);
int security_kernel_load_data(enum kernel_load_data_id id)
	ret = call_int_hook(kernel_load_data, 0, id);
	return ima_load_data(id);
void security_task_getsecid(struct task_struct *p, u32 *secid)
	call_void_hook(task_getsecid, p, secid);
EXPORT_SYMBOL(security_task_getsecid);
		struct rlimit *new_rlim)
			int sig, const struct cred *cred)
			 unsigned long arg4, unsigned long arg5)
	int rc = -ENOSYS;
		if (thisrc != -ENOSYS) {
			       struct msg_msg *msg, int msqflg)
			       struct task_struct *target, long type, int mode)
int security_shm_shmat(struct kern_ipc_perm *shp, char __user *shmaddr, int shmflg)
			unsigned nsops, int alter)
int security_getprocattr(struct task_struct *p, const char *lsm, char *name,
				char **value)
	return -EINVAL;
	return -EINVAL;
	return call_int_hook(secid_to_secctx, -EOPNOTSUPP, secid, secdata,
				seclen);

int security_unix_stream_connect(struct sock *sock, struct sock *other, struct sock *newsk)
						protocol, kern);
int security_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen)
int security_socket_connect(struct socket *sock, struct sockaddr *address, int addrlen)
int security_socket_getpeersec_stream(struct socket *sock, char __user *optval,
				      int __user *optlen, unsigned len)
				optval, optlen, len);
int security_socket_getpeersec_dgram(struct socket *sock, struct sk_buff *skb, u32 *secid)
void security_sk_classify_flow(struct sock *sk, struct flowi *fl)
	call_void_hook(sk_getsecid, sk, &fl->flowi_secid);
void security_req_classify_flow(const struct request_sock *req, struct flowi *fl)
	call_void_hook(req_classify_flow, req, fl);
int security_inet_conn_request(struct sock *sk,
			struct sk_buff *skb, struct request_sock *req)
			const struct request_sock *req)
			struct sk_buff *skb)
int security_sctp_assoc_request(struct sctp_endpoint *ep, struct sk_buff *skb)
	return call_int_hook(sctp_assoc_request, 0, ep, skb);
void security_sctp_sk_clone(struct sctp_endpoint *ep, struct sock *sk,
	call_void_hook(sctp_sk_clone, ep, sk, newsk);

int security_ib_endport_manage_subnet(void *sec, const char *dev_name, u8 port_num)
	return call_int_hook(ib_endport_manage_subnet, 0, sec, dev_name, port_num);

			      struct xfrm_sec_ctx **new_ctxp)
int security_xfrm_policy_lookup(struct xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir)
	return call_int_hook(xfrm_policy_lookup, 0, ctx, fl_secid, dir);
				       const struct flowi *fl)
	int rc = 1;
				list) {
		rc = hp->hook.xfrm_state_pol_flow_match(x, xp, fl);
void security_skb_classify_flow(struct sk_buff *skb, struct flowi *fl)
	int rc = call_int_hook(xfrm_decode_session, 0, skb, &fl->flowi_secid,
				0);


int security_key_permission(key_ref_t key_ref,
			    const struct cred *cred, unsigned perm)
	return call_int_hook(key_permission, 0, key_ref, cred, perm);
int security_key_getsecurity(struct key *key, char **_buffer)
	*_buffer = NULL;
	return call_int_hook(key_getsecurity, 0, key, _buffer);

